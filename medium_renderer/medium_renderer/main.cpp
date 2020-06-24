
#include "pch.h"

#include "SoftwareRenderer/include.h"

#include "shaders/guro_shader.h"
#include "shaders/LightSpotShader.h"

#include "scene_objects/lighterObj.h"

#define VK_UP 0x26
#define VK_DOWN 0x28

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44

//void* operator new(std::size_t sz) {
//	gui::console::printf("global op new called, size = %zu\n", sz);
//	void* ptr = std::malloc(sz);
//	if (ptr)
//		return ptr;
//	else
//		throw std::bad_alloc{};
//}
//void operator delete(void* ptr) noexcept
//{
//	gui::console::printf("global op delete called");
//	std::free(ptr);
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE no, LPSTR args, int cmdShow)
{
	gui::init(hInstance);
	gui::console::create_console();
	//gui::thread_pool.resize(64);

	// create window
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();

	// set context
	sr::set_rendering_context(window->canvas);
	

	// model
	sr::Model head("models/african_head/african_head");
	if (!head.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}

	sr::Model cube("models/cube/cube");
	if (!cube.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}

	LighterObj lighter(cube, gm::vec3(3, 0, 0), 0.05f);


	// Shader
	GuroShader guro_shader;
	LightSpotShader light_shader;

	// Camera
	sr::Camera camera(gm::vec3(0, 0, 5));
	float mouse_x = 0.5f;
	float mouse_y = 0.5f;

	float shift_x = 0.0f;
	float shift_y = 0.0f;


	//  ============= game loop ===============
	Timer timer;
	while (gui::Window::is_running(window))
	{
		// Exit by Esc
		if (gui::Input::was_pressed(VK_ESCAPE)) break;

		// clear screan and zbuffer
		sr::flush_screan(gui::Color(20));


		// ================ Process input ==================

		// Camera controll by mouse
		shift_x = gui::Mouse::pos_x - mouse_x;
		shift_y = gui::Mouse::pos_y - mouse_y;

		mouse_x = gui::Mouse::pos_x;
		mouse_y = gui::Mouse::pos_y;


		// Camera controll by keys
		if (gui::Input::pressed(VK_LEFT))
			shift_x -= timer.elapsed;

		if (gui::Input::pressed(VK_RIGHT))
			shift_x += timer.elapsed;

		if (gui::Input::pressed(VK_UP))
			shift_y += timer.elapsed;

		if (gui::Input::pressed(VK_DOWN))
			shift_y -= timer.elapsed;

		camera.ProcessMouseMovementShift(shift_x, shift_y);

		// Camera movement
		if (gui::Input::pressed(VK_W))
			camera.ProcessKeyboard(sr::FORWARD, timer.elapsed);

		if (gui::Input::pressed(VK_S))
			camera.ProcessKeyboard(sr::BACKWARD, timer.elapsed);

		if (gui::Input::pressed(VK_A))
			camera.ProcessKeyboard(sr::LEFT, timer.elapsed);

		if (gui::Input::pressed(VK_D))
			camera.ProcessKeyboard(sr::RIGHT, timer.elapsed);


		//  ================ Draw =================
		
		// Set head uniforms
		guro_shader.diffuse = &head.diffusemap;

		guro_shader.set_view(camera.get_lookat());
		guro_shader.set_projection(camera.get_projection());

		guro_shader.CameraPos = camera.Position;
		guro_shader.LightPos = lighter.Position;

		// Draw head
		sr::render_model(head, &guro_shader);

		// Set lighter uniforms
		float radius = 7.0f;
		float lightX = sinf(get_time() * 0.5f) * radius;
		float lightZ = cosf(get_time() * 0.5f) * radius;
		lighter.Position = gm::vec3(lightX, 0, lightZ);

		gm::mat4 Model;
		Model.set_col(3, lighter.Position);
		Model.set_scale(lighter.scale);

		light_shader.Transforms = camera.get_projection() * camera.get_lookat() * Model;

		// Draw cube
		sr::render_model(lighter, &light_shader);

		
		// ================ Info ouput ===================
		static float output_delay = 2.0f;
		if (output_delay -= timer.elapsed; output_delay < 0)
		{
			gui::console::printf("frame time: %f\n fps: %d\n", timer.elapsed, timer.FPS);
			output_delay = 2.0f;
		}


		// =============== System update ==================
		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
	}

	return 0;
}

#include "pch.h"

#include "SoftwareRenderer/include.h"
#include "shaders/guro_shader.h"


#define VK_UP 0x26
#define VK_DOWN 0x28

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE no, LPSTR args, int cmdShow)
{
	gui::init(hInstance);
	gui::console::create_console();

	// create window
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();

	// set context
	sr::set_rendering_context(window->canvas);
	

	// model
	sr::Model model("models/african_head/african_head");
	//sr::Model model("models/cube/cube");

	if (!model.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}

	// Shader
	GuroShader shader;

	// Camera
	sr::Camera camera(gm::vec3(0, 0, 5));
	float mouse_x = 0.5f;
	float mouse_y = 0.5f;

	float shift_x = 0.0f;
	float shift_y = 0.0f;

	gm::vec3 light_dir = gm::vec3(1, 1, 1).get_normalized();

	//  ============= game loop ===============
	Timer timer;
	while (gui::Window::is_running(window))
	{
		// Exit by Esc
		if (gui::Input::was_pressed(VK_ESCAPE)) break;

		// clear screan and zbuffer
		sr::flush_screan();


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
		
		// Set uniforms
		shader.diffuse = &model.diffusemap;
		shader.View = camera.get_lookat();
		shader.Projection = camera.get_projection();

		shader.CameraPos = camera.Position;
		shader.LightDir = light_dir;

		// Draw model
		sr::render_model(model, &shader);

		
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
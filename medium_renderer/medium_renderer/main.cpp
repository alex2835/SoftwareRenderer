
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

void print_mat(const gm::mat4& mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			gui::console::printf("%0.2f ", mat[i][j]);
		gui::console::printf("\n");
	}
	gui::console::printf("\n");
}

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

	// create window
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();

	// set context
	sr::set_rendering_context(window->canvas);
	

	// mesh
	sr::Mesh head("models/african_head/african_head");
	if (!head.valid())
	{
		gui::console::printf("Error: Can not load mesh\n");
		return 1;
	}

	sr::Mesh cube("models/cube/cube");

	if (!cube.valid())
	{
		gui::console::printf("Error: Can not load mesh\n");
		return 1;
	}

	LighterObj lighter(&cube, gm::vec3(3, 0, 0), 0.2f);


	sr::Mesh plane("models/plane/plane");
	if (!cube.valid())
	{
		gui::console::printf("Error: Can not load mesh\n");
		return 1;
	}


	// Shader
	GuroShader guro_shader;
	LightSpotShader light_shader;

	// Camera
	sr::Camera camera(gm::vec3(0, 5, 15), 90, 20);
	static float mouse_x = gui::Mouse::pos_x;
	static float mouse_y = gui::Mouse::pos_y;

	float shift_x = 0.0f;
	float shift_y = 0.0f;

	
	// On backface culling
	sr::backface_culling(&camera.Position);



	//  ====================== game loop ===========================
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
		guro_shader.CameraPos = camera.Position;
		guro_shader.LightPos = lighter.Position;


		// Set head uniforms ===============
		guro_shader.diffusemap = &head.diffusemap;

		gm::mat4 mesh_head;
		mesh_head.set_col(3, gm::vec3(-2, 0, 0));

		guro_shader.set_model(mesh_head);
		guro_shader.set_view(camera.get_lookat());
		guro_shader.set_projection(camera.get_projection());

		// Draw head
		sr::render_mesh(head, &guro_shader);


		// Set plane uniforms ================
		guro_shader.diffusemap = &plane.diffusemap;

		gm::mat4 mesh_plane;
		mesh_plane.set_col(3, gm::vec3(0, -1, -2));
		mesh_plane.set_scale(gm::vec3(0.5f, 1.0f, 0.5f));

		guro_shader.set_model(mesh_plane);
		guro_shader.set_view(camera.get_lookat());
		guro_shader.set_projection(camera.get_projection());

		// Draw plane
		sr::render_mesh(plane, &guro_shader);


		// Set cube uniforms ================
		guro_shader.diffusemap = &plane.diffusemap;

		mesh_plane.set_col(3, gm::vec3(2, -0.5, 0));
		mesh_plane.set_scale(0.2f);

		guro_shader.set_model(mesh_plane);
		guro_shader.set_view(camera.get_lookat());
		guro_shader.set_projection(camera.get_projection());

		// Draw plane
		sr::render_mesh(cube, &guro_shader);

		
		// Set lighter uniforms ==============
		gm::mat4 model;
		float radius = 7.0f;
		float lightX = sinf(get_time() * 0.5f) * radius;
		float lightZ = cosf(get_time() * 0.5f) * radius;
		lighter.Position = gm::vec3(lightX, 3.0f, lightZ);

		model.set_col(3, lighter.Position);
		model.set_scale(lighter.scale);

		light_shader.Model = model;
		light_shader.View = camera.get_lookat();
		light_shader.Transforms = camera.get_projection() * camera.get_lookat() * model;

		// Draw lighter
		sr::render_mesh(*lighter.mesh, &light_shader);

		

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
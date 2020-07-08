
#include "pch.h"

#include "SoftwareRenderer/include.h"

#include "shaders/guro_shader.h"
#include "shaders/phong_shader.h"
#include "shaders/LightSpotShader.h"

#include "scene_objects/lighterObj.h"


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
	
	
	// lighter cube mesh
	sr::Mesh cubeMesh("models/cube/cube");
	if (!cubeMesh.valid())
		return 1;
	
	LighterObj lighter(&cubeMesh, gm::vec3(3, 0, 3), 0.2f);
	LighterObj lighter2(&cubeMesh, gm::vec3(-4, 4, -13), 0.2f);


	// Models
	sr::Model cube("models/cube", gm::vec3(2, -0.5f, 0), 0.2f);
	if (!cube.valid())
		return 1;

	sr::Model head("models/african_head", gm::vec3(-3, 0 , 0));
	if (!head.valid())
		return 1;

	sr::Model diablo("models/diablo3_pose", gm::vec3(2, 1, -16), 2);
	if (!head.valid())
		return 1;

	sr::Model plane("models/plane", gm::vec3(0, -1, -8), gm::vec3(0.5f, 1.0f, 1.0f));
	if (!plane.valid())
		return 1;

	sr::Model boggie("models/boggie", gm::vec3(-2, 1, -16), 2);
	if (!boggie.valid())
		return 1;


	// Shader
	shaders::GuroShader shader;
	shaders::LightSpotShader light_shader;


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
		shader.CameraPos = camera.Position;
		shader.lighters[0] = sr::create_spot_lighter(lighter.Position);
		shader.lighters[1] = sr::create_dir_lighter(lighter2.Position);
		shader.nLighters = 2;
		shader.material.specular = 0.3f;

		shader.set_view(camera.get_lookat());
		shader.set_projection(camera.get_projection());


		// Draw models
		head.draw(&shader);
		plane.draw(&shader);
		diablo.draw(&shader);
		cube.draw(&shader);
		boggie.draw(&shader);

		
		// Set lighter uniforms ==============
		gm::mat4 model;
		float radius = 5.0f;
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


		// second lighter
		model.set_col(3, lighter2.Position);
		model.set_scale(lighter2.scale);

		light_shader.Model = model; 
		light_shader.View = camera.get_lookat();
		light_shader.Transforms = camera.get_projection() * camera.get_lookat() * model;

		// Draw lighter
		sr::render_mesh(*lighter2.mesh, &light_shader);

		
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
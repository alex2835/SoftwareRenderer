
#include "include.h"

#include "window/window.h"
#include "io/log.h"
#include "libs/thread_pool.h"
#include "image/draw.h"

#include "shaders/guro_shader.h"
#include "shaders/phong_shader.h"
#include "shaders/light_shader.h"

#define VK_UP 0x26
#define VK_DOWN 0x28

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44


// Camera mouse controll
static float mouse_x = gui::Mouse::pos_x;
static float mouse_y = gui::Mouse::pos_y;
float shift_x = 0.0f;
float shift_y = 0.0f;

bool process_input(Timer &timer, sr::Camera &camera)
{
	// Exit by Esc
	if (gui::Input::was_pressed(VK_ESCAPE))
		return false;

	// Camera control by mouse
	shift_x = gui::Mouse::pos_x - mouse_x;
	shift_y = gui::Mouse::pos_y - mouse_y;

	mouse_x = gui::Mouse::pos_x;
	mouse_y = gui::Mouse::pos_y;

	// Camera control by keys
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

	return true;
}

void print_system_info( Timer& timer )
{
	static float output_delay = 2.0f;
	if (output_delay -= timer.elapsed; output_delay < 0)
	{
		gui::console::printf("frame time: %f\n fps: %d\n", timer.elapsed, timer.FPS);
		printf("frame time: %f\n fps: %d\n", timer.elapsed, timer.FPS);
		output_delay = 2.0f;
	}
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE no, PWSTR args, int cmdShow)
{
	// window
	gui::init(hInstance);
	gui::console::create_console();

	gui::Window* window = new gui::Window(L"Window", 800, 600);
	window->canvas.set_max_buffer_size();

	// Renderer
	Timer timer;
	renderer::Renderer renderer(window->canvas);

	auto lighter_pos = gm::vec3(3, 0, 3);
	renderer.GetLighters() = {sr::create_spot_lighter(lighter_pos)};

	shaders::GuroShader shader;
	shaders::lightSpot_shader light_shader;
	renderer.GetModels() = std::vector<sr::Model>{sr::Model("models/cube", shader, gm::vec3(2, -0.5f, 0), 0.2f),
																 sr::Model("models/african_head", shader, gm::vec3(-3, 0, 0)),
																 sr::Model("models/diablo3_pose", shader, gm::vec3(2, 1, -16), 2),
																 sr::Model("models/plane", shader, gm::vec3(0, -1, -8), gm::vec3(0.5f, 1.0f, 1.0f)),
																 sr::Model("models/boggie", shader, gm::vec3(-2, 1, -16), 2),
																 sr::Model("models/cube", light_shader, lighter_pos, 0.2f)};

	// Game loop
	while( gui::Window::is_running( window ) )
	{
		print_system_info( timer );
		if( !process_input( timer, renderer.GetCamera() ) )
			break;

		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
		renderer.UpdateRenderer();
	}

	return 0;
}
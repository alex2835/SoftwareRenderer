
#include "window/window.h"
#include "io/log.h"
#include "libs/thread_pool.h"
#include "image/draw.h"
#include "geometry/geometry.h"


#include "renderer/renderer.h"
#include "shader/shader.h"

// Tests
//#include "tests/geometry_test.h"


struct MyShader : renderer::Shader
{
	void fragment()
	{

	}

	void vertex()
	{

	}
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE no, LPSTR args, int cmdShow)
{
	gui::init(hInstance);
	gui::console::create_console();

	gui::thread_pool.resize(16);

	// create window
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();


	// set context
	renderer::set_rendering_context(window->canvas);
	

	// model
	renderer::Model model("models/african_head/african_head");
	//renderer::Model model("models/cube/cube");

	if (!model.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}


	//SetCapture(window->hwnd);

	// light dir
	gm::vec3 light_dir(0, 0, -1);


	Timer timer;
	while (gui::Window::is_running(window))
	{

		if (gui::Input::was_pressed(VK_ESCAPE))
			break;

		renderer::flush_screan();
		
		MyShader shader;
		renderer::render_model(model, shader, timer.elapsed);

		
		static float output_delay = 10.0f;
		if (output_delay -= timer.elapsed; output_delay < 0)
		{
			gui::console::printf("frame time: %f\n fps: %d\n", timer.elapsed, timer.FPS);
			output_delay = 10.0f;
		}


		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
	}

	return 0;
}
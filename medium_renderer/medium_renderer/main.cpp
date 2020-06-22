
#include "pch.h"

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
	sr::set_rendering_context(window->canvas);
	

	// model
	sr::Model model("models/african_head/african_head");
	//sr::Model model("models/cube/cube");

	if (!model.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}



	//  ============= game loop ===============
	Timer timer;
	while (gui::Window::is_running(window))
	{

		if (gui::Input::was_pressed(VK_ESCAPE))
			break;

		sr::flush_screan();
		
		MyShader shader;
		sr::render_model(model, shader, timer.elapsed);

		
		static float output_delay = 3.0f;
		if (output_delay -= timer.elapsed; output_delay < 0)
		{
			gui::console::printf("frame time: %f\n fps: %d\n", timer.elapsed, timer.FPS);
			output_delay = 3.0f;
		}

		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
	}

	return 0;
}
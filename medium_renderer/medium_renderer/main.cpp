

#include "window/window.h"
#include "io/log.h"
#include "libs/thread_pool.h"
#include "image/draw.h"
#include "geometry/geometry.h"


#include "renderer/renderer.h"

#include "shader/shader.h"
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
	// create window
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();


	// set context
	renderer::set_rendering_context(window->canvas);
	

	// model
	renderer::Model model("models/african_head_jpg/african_head");

	if (!model.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}



	// light dir
	gm::vec3 light_dir(0, 0, -1);



	gui::Timer timer(60);
	while (gui::Window::is_running(window))
	{

		renderer::flush_screan();
		
		MyShader shader;
		renderer::render_model(model, shader);


		gui::console::printf("fps: %d\n", timer.FPS);



		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
	}

	return 0;
}

#include "renderer.h"


namespace renderer
{

	// context
	gui::Image_base<uint8_t>* context = NULL;

	// zbuffer
	int zbuffer_size = 0;
	float* zbuffer = NULL;


	// set rendering context
	void set_rendering_context(gui::Image_base<uint8_t>& rendering_context)
	{
		context = &rendering_context;

		// set def zbuffer_size
		zbuffer_resize(context->whole_size);
	}

	
	// flush zbuffer
	void flush_zbuffer()
	{
		memset(zbuffer, 0, zbuffer_size * sizeof(float));
	}


	// resize zbuffer
	void zbuffer_resize(int size)
	{
		delete[] zbuffer;
		zbuffer_size = size;
		zbuffer = new float[zbuffer_size];
	}


	// flush screan
	void flush_screan(const gui::Color& color)
	{
		// reallocate zbuffer if neccessery
		if (zbuffer_size < context->whole_size)
			zbuffer_resize(context->whole_size);

		flush_zbuffer();
		gui::cpu::draw_filled_rect_async(*context, 0.0f, 0.0f, 1.0f, 1.0f, color);
	}


#define VK_UP 0x26
#define VK_DOWN 0x28

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44



	// render model
	void render_model(Model& model, Shader& shader, float elapsed)
	{
		
		static renderer::Camera camera(gm::vec3(1, 1, 1));

		static float mouse_x = 0.5f;
		static float mouse_y = 0.5f;

		float shift_x = gui::Mouse::pos_x - mouse_x;
		float shift_y = gui::Mouse::pos_y - mouse_y;

		if (gui::Input::pressed(VK_LEFT))
			shift_x -= elapsed;

		if (gui::Input::pressed(VK_RIGHT))
			shift_x += elapsed;


		if (gui::Input::pressed(VK_UP))
			shift_y += elapsed;

		if (gui::Input::pressed(VK_DOWN))
			shift_y -= elapsed;


		mouse_x = gui::Mouse::pos_x;
		mouse_y = gui::Mouse::pos_y;

		camera.ProcessMouseMovementShift(shift_x, shift_y);


		if (gui::Input::pressed(VK_W))
			camera.ProcessKeyboard(FORWARD, elapsed);

		if (gui::Input::pressed(VK_S))
			camera.ProcessKeyboard(BACKWARD, elapsed);

		if (gui::Input::pressed(VK_A))
			camera.ProcessKeyboard(LEFT, elapsed);

		if (gui::Input::pressed(VK_D))
			camera.ProcessKeyboard(RIGHT, elapsed);


		gm::mat4 Model;

		gm::mat4 View = camera.get_lookat();
		gm::mat4 Projection = camera.get_projection();

		gm::mat4 ViewPort = gm::viewport(context->width / 8,
										 context->height / 8,
										 context->width * 3 / 4,
										 context->height * 3 / 4);
		

		gm::mat4 transorms = Projection * View * Model;

		//gui::thread_pool.parallel_for_void(0, model.faces_size(),
		//	[&model, &transorms](int from, int to)
		//	{
		//		for (int i = from; i < to; i++)
				for (int i = 0; i < model.faces_size(); i++)
				{
					bool fit = false;
					Face& face = model.get_face(i);

					gm::vec3 screen_coords[3];
					gm::vec2i uv[3];

					for (int j = 0; j < 3; j++)
					{
						// get uv
						uv[j] = gm::vec2i(model.diffusemap.width * face[j].uv.x,
										  model.diffusemap.height * face[j].uv.y);
						
						// get
						gm::vec3& v = face[j].vert;

						
						// TODO: call here the vertex shader (instead this)

						// matrix transformations
						screen_coords[j] = (transorms * gm::mat4(v)).toVec3();

						
						// clip
						if (screen_coords[j].z > 5.0f && screen_coords[j].z < 10.0f)
							fit = true;

						// view port
						screen_coords[j] = (ViewPort * gm::mat4(screen_coords[j])).toVec3();
					}

					if (fit) 
					renderer::rasterizer::triangle(*context, screen_coords, uv, zbuffer, model);
				}
		//	}
		//);
		//gui::thread_pool.wait();

	}

}
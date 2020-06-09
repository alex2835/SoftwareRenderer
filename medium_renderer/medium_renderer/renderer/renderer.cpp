
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





	// temp
	gm::vec3 light_dir = gm::vec3(1, -1, 1).get_normalized();
	gm::vec3 eye(1, 1, 3);
	gm::vec3 center(0, 0, 0);


	// render model
	void render_model(Model& model, Shader& shader)
	{
		
		static renderer::Camera camera;

		camera.MouseSensitivity = 100;

		static float mouse_x = 0.5f;
		static float mouse_y = 0.5f;

		float shift_x = gui::Mouse::pos_x - mouse_x;
		float shift_y = gui::Mouse::pos_y - mouse_y;

		mouse_x = gui::Mouse::pos_x;
		mouse_y = gui::Mouse::pos_y;

		camera.ProcessMouseMovement(shift_x, shift_y);


		gm::mat4 ModelView = camera.get_lookat();

		//gm::mat4 ModelView = gm::lookat(eye, center);

		gm::mat4 Projection = gm::projection(90.0f, 0.1f, 120.0f);

		// camera located on z axis
		//Projection[3][2] = -1.0f / (eye - center).norm();


		gm::mat4 ViewPort = gm::viewport(context->width / 8,
										 context->height / 8,
										 context->width * 3 / 4,
										 context->height * 3 / 4);

		

		gm::mat4 transorms = ViewPort * Projection * ModelView;

		ASYNC_FOR(0, model.faces_size())
			[from, to, &model, &transorms]()//&ViewPort, &Projection, &ModelView]()
			{
				for (int i = from; i < to; i++)
				{
					Face& face = model.get_face(i);

					// TODO: call here the vertex shader (instead this)

					gm::vec3 screen_coords[3];
					gm::vec3 world_coords[3];
					gm::vec2i uv[3];

					for (int j = 0; j < 3; j++)
					{
						// get uv
						uv[j] = gm::vec2i (model.diffusemap.width * face[j].uv.x, 
										   model.diffusemap.height * face[j].uv.y);

						// get
						gm::vec3& v = face[j].vert;

						// matrix transformations
						//screen_coords[j] = (ViewPort * Projection * ModelView * gm::mat4(v)).toVec3();
						screen_coords[j] = (transorms* gm::mat4(v)).toVec3();

						world_coords[j] = v;
					}

					
					renderer::rasterizer::triangle(*context, screen_coords, uv, zbuffer, model);
				}
			}
		END_FOR
	}

}
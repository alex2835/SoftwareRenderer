
#include "renderer.h"


namespace renderer
{

	// context
	gui::Image_base<uint8_t>* context = NULL;

	// zbuffer
	static int zbuffer_size = 0;
	static float* zbuffer = NULL;

	// shaders memory
	static int shaders_memory_size = 0;
	static char* shaders_memory = NULL;

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

	// release
	void release()
	{
		delete[] zbuffer;
		delete[] shaders_memory;
	}



	// render model
	void render_model(Model& model, Shader* in_shader)
	{
		// Split while mesh on tasts
		// and put them on thread pool
		const int tasks = __min(8, model.faces_size());

		// Get actual viewport
		gm::mat4 ViewPort = gm::get_viewport(context->width, context->height);

		// reallocate memory for shaders for each task
		if (shaders_memory_size < in_shader->size() * tasks)
		{
			delete[] shaders_memory;
			shaders_memory_size = in_shader->size() * tasks;
			shaders_memory = new char[shaders_memory_size];
		}

		//if (tasks > 64)
		//{
			// Call here Vertex shader and then rasterize trianle
			//auto futures = gui::thread_pool.parallel_for(0, model.faces_size(),
			//	[&](int from, int to, int id)
			//	{
			//		// TODO: make this allocatetion on stack
		Shader* shader = in_shader;// ->clone(shaders_memory + in_shader->size() * id);

					//for (int i = from; i < to; i++)
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

							// Vertex shader
							auto [vertex, discard] = shader->vertex(face[j].vert, face[j].norm, j);

							// add vertex to triangle
							screen_coords[j] = vertex;

							// clip
							if (!discard && screen_coords[j].z > 5.0f && screen_coords[j].z < 9.5f)
								fit = true;

							// view port
							screen_coords[j] = (ViewPort * gm::mat4(screen_coords[j])).toVec3();
						}

						// Rasterize triangle
						if (fit) {
							rasterizer::triangle(*context, screen_coords, uv, zbuffer, shader);
						}
			//		}
			//
			//		delete shader;
				}
			//);

			//for (auto& future : futures)
			//	future.get();

			//gui::thread_pool.wait();


		//	for (int i = 0; i < model.faces_size(); i++)
		//	{
		//		bool fit = false;
		//		Face& face = model.get_face(i);
		//
		//		gm::vec3 screen_coords[3];
		//		gm::vec2i uv[3];
		//
		//		for (int j = 0; j < 3; j++)
		//		{
		//			// get uv
		//			uv[j] = gm::vec2i(model.diffusemap.width * face[j].uv.x,
		//				model.diffusemap.height * face[j].uv.y);
		//
		//			// Vertex shader
		//			auto [vertex, discard] = in_shader->vertex(face[j].vert, face[j].norm, j);
		//
		//			// add vertex to triangle
		//			screen_coords[j] = vertex;
		//
		//			// clip
		//			if (!discard && screen_coords[j].z > 5.0f && screen_coords[j].z < 9.5f)
		//				fit = true;
		//
		//			// view port
		//			screen_coords[j] = (ViewPort * gm::mat4(screen_coords[j])).toVec3();
		//		}
		//
		//		// Rasterize triangle
		//		if (fit) {
		//			rasterizer::triangle(*context, screen_coords, uv, zbuffer, in_shader);
		//		}
		//	}

	}

}
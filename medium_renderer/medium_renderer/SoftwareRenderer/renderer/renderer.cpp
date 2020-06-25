
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

	// results
	std::future<void>* future = new std::future<void>[256];

	// Backface culling
	static gm::vec3* CameraPos;
	static bool backface_culling_active = false;

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


	// take a viewer position
	void backface_culling(gm::vec3* cameraPos)
	{
		backface_culling_active = cameraPos;
		CameraPos = cameraPos;
	}


	// release
	void release()
	{
		delete[] zbuffer;
		delete[] shaders_memory;
		delete[] future;
	}


	// render model
	void render_model(Model& model, Shader* in_shader)
	{
		// Split while mesh on tasts
		// and put them on thread pool
		const int tasks = __min(128, model.faces_size());

		// Get actual viewport
		gm::mat4 ViewPort = gm::get_viewport(context->width, context->height);

		// reallocate memory for shaders for each task
		if (shaders_memory_size < in_shader->size() * tasks)
		{
			delete[] shaders_memory;
			shaders_memory_size = in_shader->size() * tasks;
			shaders_memory = new char[shaders_memory_size];
		}

		for (int i = 0; i < tasks; i++)
		{
			int from = i * model.faces_size() / tasks;
			int to = (i + 1) * model.faces_size() / tasks;

			future[i] = gui::thread_pool.add_task(
				[&, from, to, id = i, in_shader]()
				{
					// Create copy for this thread (No memory allocation)
					Shader* shader = in_shader->clone(shaders_memory + in_shader->size() * id);

					for (int i = from; i < to; i++)
					{
						cull:
						bool fit = false;
						bool cull = true;

						Face& face = model.get_face(i);

						gm::vec3 screen_coords[3];
						gm::vec2i uv[3];

						for (int j = 0; j < 3; j++)
						{
							// get uv
							uv[j] = gm::vec2i(model.diffusemap.width * face[j].uv.x,
								model.diffusemap.height * face[j].uv.y);

							// Vertex shader
							auto [vertex, global, normal] = shader->vertex(face[j].vert, face[j].norm, j);

							// backface culling
							if (backface_culling_active)
							{
								global -= *CameraPos;
								cull = (*CameraPos - global).normalize() * normal < -0.5f;
							}

							// clip
							if (vertex.z > 5.0f && vertex.z < 6.5f)
								fit = true;

							// view port
							screen_coords[j] = (ViewPort * gm::mat4(vertex)).toVec3();
						}

						// Rasterize triangle
						if (fit && !cull) {
							rasterizer::triangle(*context, screen_coords, uv, zbuffer, shader);
						}
					}
				}
			);
		}
		for (int i = 0; i < tasks; i++)
			future[i].get();
	}

}
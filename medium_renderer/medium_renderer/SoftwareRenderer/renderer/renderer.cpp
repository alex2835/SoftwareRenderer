
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



	// render model
	void render_model(Model& model, Shader* shader)
	{
		gm::mat4 ViewPort = gm::get_viewport(context->width, context->height);
	
	//	gui::thread_pool.parallel_for_void(0, model.faces_size(), 64,
	//		[&, shader](int from, int to)
	//		{
	//			for (int i = from; i < to; i++)
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
						auto[vertex, normal] = shader->vertex(face[j].vert, face[j].norm, j);
						
						// add vertex to triangle
						screen_coords[j] = vertex;
						
						// clip
						if (screen_coords[j].z > 5.0f && screen_coords[j].z < 10.0f)
							fit = true;

						// backface culling
						// ...

						// view port
						screen_coords[j] = (ViewPort * gm::mat4(screen_coords[j])).toVec3();
					}

					// Rasterize triangle
					if (fit)
						rasterizer::triangle(*context, screen_coords, uv, zbuffer, shader);
				}
	//		}
	//	);
	//	gui::thread_pool.wait();
	}

}
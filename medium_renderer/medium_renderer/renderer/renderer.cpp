
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
		gm::mat4 ModelView = lookat(eye, center);
		gm::mat4 Projection;

		gm::mat4 ViewPort = viewport(context->width / 8,
									 context->height / 8,
									 context->width * 3 / 4,
									 context->height * 3 / 4);

		Projection[3][2] = -1.f / (eye - center).norm();


		for (int i = 0; i < model.faces_size(); i++)
		{

			std::vector<int> face = model.face(i);
			gm::vec3 screen_coords[3];
			gm::vec3 world_coords[3];
			for (int j = 0; j < 3; j++)
			{
				gm::vec3 v = model.get_vert(face[j]);
				
				screen_coords[j] = (ViewPort * Projection * ModelView * gm::mat4(v)).toVec3();
				//screen_coords[j] = gm::vec3(v.x * context->width / 2 +  context->width / 2,
				//							v.y * context->height / 2 + context->height / 2,
				//							v.z);
				world_coords[j] = v;
			}

			gm::vec3 n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);

			
			n.normalize();
			float intensity = n * light_dir;
			intensity = intensity < 0 ? 0.1 : intensity;

			gm::vec2i uv[3];
			for (int k = 0; k < 3; k++)
				uv[k] = model.get_uv(i, k);


			renderer::rasterizer::triangle(*context, screen_coords, uv, zbuffer, model);
		}
	}


	// matrix generation

	gm::mat4 lookat(const gm::vec3& eye, const gm::vec3& center, const gm::vec3& up)
	{
		gm::vec3 z = (eye - center).get_normalized();
		gm::vec3 x = (up ^ z).get_normalized();
		gm::vec3 y = (z ^ x).get_normalized();

		gm::mat4 res;
		for (int i = 0; i < 3; i++) {
			res[0][i] = x[i];
			res[1][i] = y[i];
			res[2][i] = z[i];
			res[i][3] = -center[i];
		}
		return res;
	}


	gm::mat4 viewport(int x, int y, int w, int h, int depth)
	{
		gm::mat4 m;
		m[0][3] = x + w / 2.f;
		m[1][3] = y + h / 2.f;
		m[2][3] = depth / 2.f;

		m[0][0] = w / 2.f;
		m[1][1] = h / 2.f;
		m[2][2] = depth / 2.f;
		return m;
	}

}
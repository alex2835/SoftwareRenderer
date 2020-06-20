
#include "renderer.h"



void print_mat(const gm::mat4& mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			gui::console::printf("%0.2f ", mat[i][j]);
		gui::console::printf("\n");
	}
	gui::console::printf("\n");
}





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





	// temp
	gm::vec3 light_dir = gm::vec3(1, -1, 1).get_normalized();
	gm::vec3 eye(1, 1, 1);
	gm::vec3 center(0, 0, 0);


	// render model
	void render_model(Model& model, Shader& shader)
	{
		
		static renderer::Camera camera(eye);

		camera.MouseSensitivity = 500;

		static float mouse_x = 0.5f;
		static float mouse_y = 0.5f;

		float shift_x = gui::Mouse::pos_x - mouse_x;
		float shift_y = gui::Mouse::pos_y - mouse_y;

		mouse_x = gui::Mouse::pos_x;
		mouse_y = gui::Mouse::pos_y;

		camera.ProcessMouseMovement(shift_x, shift_y);

		center.x += shift_x;
		center.y += shift_y;

		static float x = 0;
		static float y = 0;
		static float z = 0;

		if (gui::Input::pressed(VK_UP))
			x += 0.01f;

		if (gui::Input::pressed(VK_DOWN))
			x -= 0.01f;


		if (gui::Input::pressed(VK_W))
			camera.ProcessKeyboard(FORWARD, 0.01f);

		if (gui::Input::pressed(VK_S))
			camera.ProcessKeyboard(BACKWARD, 0.01f);

		if (gui::Input::pressed(VK_A))
			camera.ProcessKeyboard(LEFT, 0.01f);

		if (gui::Input::pressed(VK_D))
			camera.ProcessKeyboard(RIGHT, 0.01f);


		
		gm::mat4 Model;
		//Model[0][0] = 0.1f;
		//Model[1][1] = 0.1f;
		//Model[2][2] = 0.1f;
		Model[0][3] = x;
		Model[1][3] = y;
		Model[2][3] = z;

		gm::mat4 View = camera.get_lookat();
		//gm::mat4 View = gm::lookat(eye, center);

		//gm::mat4 Projection = gm::projection(90.0f, 0.1f, 120.0f);

		gm::mat4 Projection;
		Projection[3][2] = -1.0f / (eye - center).norm();

		//print_mat(View);
		//print_mat(Projection);


		gm::mat4 ViewPort = gm::viewport(context->width / 8,
										 context->height / 8,
										 context->width * 3 / 4,
										 context->height * 3 / 4);
		

		//gm::mat4 transorms = ViewPort * Projection * View * Model;
		gm::mat4 transorms = Projection * View * Model;

		//ASYNC_FOR(0, model.faces_size())
		//	[from, to, &model, &transorms]()//&ViewPort, &Projection, &ModelView]()
		//	{
		//		for (int i = from; i < to; i++)
				for (int i = 0; i < model.faces_size(); i++)
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
						screen_coords[j] = (transorms * gm::mat4(v)).toVec3();

						screen_coords[j].x = (screen_coords[j].x + 1.0f) * context->width / 2;
						screen_coords[j].y = (screen_coords[j].y + 1.0f) * context->height / 2;

						world_coords[j] = v;
					}

					
					renderer::rasterizer::triangle(*context, screen_coords, uv, zbuffer, model);
				}
		//	}
		//END_FOR
	}

}
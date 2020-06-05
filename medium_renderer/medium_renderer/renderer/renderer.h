#pragma once

#include <cstring>

#include "image/Image_base.h"
#include "image/draw.h"

#include "../rasterizer/rasterizer.h"
#include "../medel/model.h"
#include "../shader/shader.h"

namespace renderer
{
	// rendering context
	extern gui::Image_base<uint8_t>* context;

	void set_rendering_context(gui::Image_base<uint8_t>& rendering_context);


	// zbuffer
	extern int zbuffer_size;
	extern float* zbuffer;



	void flush_screan(const gui::Color& color = gui::Color(0));

	void flush_zbuffer();

	void zbuffer_resize(int size);

	void render_model(Model& model, Shader& shader);


	// matrix generation

	gm::mat4 lookat(const gm::vec3& eye, 
					const gm::vec3& center,
					const gm::vec3& up = gm::vec3(0, 1, 0));


	gm::mat4 viewport(int x, int y, int w, int h, int depth = 255);

}
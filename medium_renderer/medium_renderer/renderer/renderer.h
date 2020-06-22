#pragma once

#include <cstring>

#include "image/Image_base.h"
#include "image/draw.h"

#include "../rasterizer/rasterizer.h"
#include "../medel/model.h"
#include "../shader/shader.h"
#include "../camera/camera.h"
#include "context.h"

#include "libs/time.h"
#include "io/input.h"

#include "io/log.h"

namespace renderer
{
	
	void set_rendering_context(gui::Image_base<uint8_t>& rendering_context);

	void flush_screan(const gui::Color& color = gui::Color(0));

	void flush_zbuffer();

	void zbuffer_resize(int size);

	void render_model(Model& model, Shader& shader, float elapsed);

}
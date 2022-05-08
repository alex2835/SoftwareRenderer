
#include <utility>
#include <limits>
#include <cstdlib>

#include "../geometry/geometry.h"
#include "image/image_base.h"
#include "image/color.h"

#include "../model/model.h"
#include "../shader/shader.h"

#include "io/log.h"

namespace renderer
{
	namespace rasterizer
	{
		void triangle(gui::Image_base<uint8_t>& surface, gm::vec3* pts, gm::vec2i* uv, float* zbuffer, Shader* shader);
	}
}

#include <utility>
#include <limits>
#include <cstdlib>

#include "../geometry/geometry.h"
#include "image/image_base.h"
#include "image/color.h"

#include "../medel/model.h"
#include "../shader/shader.h"

#include "io/log.h"

namespace renderer
{

	namespace rasterizer
	{

		// barycentric coorditans
		bool barycentric(const gm::vec3& A, const gm::vec3& B, const gm::vec3& C,
						 const gm::vec3i& P, gm::vec3* out);

		// rasterize triangle
		void triangle(gui::Image_base<uint8_t>& surface, gm::vec3* pts, gm::vec2i* uv, float* zbuffer, Model& model);

	}

}
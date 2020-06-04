
#include <utility>
#include <limits>
#include <cstdlib>

#include "../geometry/geometry.h"
#include "image/canvas.h"
#include "image/color.h"


namespace rasterizer
{

	// barycentric coorditans
	bool barycentric(gm::vec3 A, gm::vec3 B, gm::vec3 C, gm::vec3i P, gm::vec3* out);

	// rasterize triangle
	void triangle(Canvas surface, gm::vec3* pts, gm::vec2i* uv, float* zbuffer, Model& model, float intensity);

}
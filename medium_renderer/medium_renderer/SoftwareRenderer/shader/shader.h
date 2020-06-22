#pragma once

#include "../geometry/geometry.h"
#include "image/color.h"

namespace renderer
{
	struct Shader
	{
		// output: { vertex, normal }
		virtual std::tuple<gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm) = 0;
		
		// output: final color
		virtual gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) = 0;
		
		virtual ~Shader() = default;
	};

}
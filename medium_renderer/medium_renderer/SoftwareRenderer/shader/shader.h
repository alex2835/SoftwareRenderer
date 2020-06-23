#pragma once

#include <tuple>

#include "../geometry/geometry.h"
#include "image/color.h"

namespace renderer
{
	struct Shader
	{
		// output: { vertex, normal }
		virtual std::tuple<gm::vec3, bool> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx);
		
		// output: final color
		virtual gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar);
		
		// return 
		virtual Shader* clone() = 0;

		// must return sizeof(OurShaderClass)
		virtual int size() = 0;


		virtual ~Shader() = default;
	};

}
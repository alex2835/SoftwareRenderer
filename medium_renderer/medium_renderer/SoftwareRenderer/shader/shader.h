#pragma once

#include <tuple>

#include "../geometry/geometry.h"
#include "image/color.h"

namespace renderer
{
	/*
		No dynamic allocations in shader such a std::vector<Lighters>
		distryctor will not be called, and memory leak.
	*/
	struct Shader
	{
		// output: { vec3 vertex, bool disacard }
		virtual std::tuple<gm::vec3, bool> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx) = 0;
		
		// output: final color
		virtual gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) = 0;
		
		// return new(memory) OurShader(*this);
		virtual Shader* clone(char* memory) = 0;

		// return sizeof(OurShaderClass);
		virtual int size() = 0;

		virtual ~Shader() = default;
	};

}
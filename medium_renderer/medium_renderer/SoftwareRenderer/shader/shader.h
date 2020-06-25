#pragma once

#include <tuple>

#include "../geometry/geometry.h"
#include "image/image.h"

namespace renderer
{
	/*
		Don't dynamic allocate in shader such a std::vector<Lighters>
		distryctor will not be called, and memory leak.
	*/
	struct Shader
	{
		union
		{
			struct {
				gui::Image* diffusemap;
				gui::Image* normalmap;
				gui::Image* heightmap;
			};
			gui::Image* maps[3];
		};

		gm::mat4 Transforms;
		gm::mat4 ModelIT;

		gm::mat4 Model;
		gm::mat4 View;
		gm::mat4 Projection;
		
		// output: { vec3 on plane vertex, vec3 in_global_space, vec3 normal_in_global_space}
		virtual std::tuple<gm::vec3, gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx) = 0;
		
		// output: final color
		virtual gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) = 0;

		// set matrix
		void set_model(const gm::mat4& model);
		void set_view(const gm::mat4& view);
		void set_projection(const gm::mat4& projection);
		
		// return new(memory) OurShader(*this);
		virtual Shader* clone(void* memory) = 0;

		// return sizeof(OurShaderClass);
		virtual int size() = 0;

		virtual ~Shader() = default;
	};

}
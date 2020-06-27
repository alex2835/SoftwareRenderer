#pragma once

#include <tuple>

#include "../geometry/geometry.h"
#include "image/image.h"
#include "material.h"
#include "../model/face.h"
#include "light.h"


namespace renderer
{
	using namespace gm;

	/*
		Don't dynamic allocate in shader such a std::vector<Lighters>
		distryctor will not be called, and memory leak.
	*/
	struct Shader
	{
		mat4 Transforms;
		mat4 ModelIT;

		mat4 Model;
		mat4 View;
		mat4 Projection;

		Material material;

		int nLighters = 0;
		Light lighters[3];
		
		// output: { vec3 vertex on plane, vec3 vertex in global space, vec3 normal in global space}
		virtual std::tuple<vec3, vec3, vec3> vertex(const Face& face, int idx) = 0;
		
		// output: final color
		virtual gui::Color fragment(const vec2i& uv, const vec3& bar) = 0;

		// set matrix
		void set_model(const mat4& model);
		void set_view(const mat4& view);
		void set_projection(const mat4& projection);
		
		// return new(memory) OurShader(*this);
		virtual Shader* clone(void* memory) = 0;

		// return sizeof(OurShaderClass);
		virtual int size() = 0;

		virtual ~Shader() = default;
	};
}
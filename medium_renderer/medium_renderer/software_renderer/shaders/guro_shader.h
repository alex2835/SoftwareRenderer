#pragma once

#include "../shader/shader.h"

namespace shaders
{
	using namespace renderer;

	struct GuroShader : Shader
	{
		vec3 LightStrengt;

		std::tuple<vec3, vec3, vec3>
			vertex(const Face& face, int idx) override;

		gui::Color
			fragment(const vec2i& uv, const vec3& bar) override;

		GuroShader* clone(void* memory) override;
		int size() override;
	};
}
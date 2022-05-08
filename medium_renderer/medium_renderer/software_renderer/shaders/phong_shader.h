#pragma once

#include "../shader/shader.h"


namespace shaders
{
	using namespace renderer;

	struct PhongShader : Shader
	{
		vec3 CameraPos;
		vec3 LightStrengt;

		vec3 verts[3];
		vec3 norms[3];
		vec3 global_poss[3];
		vec3 norms_out[3];

		std::tuple<vec3, vec3, vec3>
			vertex(const Face& face, int idx) override;

		gui::Color
			fragment(const vec2i& uv, const vec3& bar) override;

		PhongShader* clone(void* memory) override;
		int size() override;
	};
}
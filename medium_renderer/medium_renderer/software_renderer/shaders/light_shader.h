#pragma once

#include "../shader/shader.h"
#include "../geometry/geometry.h"


namespace shaders
{
	using namespace renderer;

	struct lightSpot_shader : Shader
	{
		gui::Color color = gui::Color(255);

		std::tuple<vec3, vec3, vec3> vertex(const Face& face, int idx) override;

		gui::Color fragment(const vec2i& uv, const vec3& bar) override;

		lightSpot_shader* clone(void* memory);

		int size();
	};
}
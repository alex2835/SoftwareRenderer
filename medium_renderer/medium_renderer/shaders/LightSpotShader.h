#pragma once

#include "../SoftwareRenderer/shader/shader.h"
#include "../SoftwareRenderer/geometry/geometry.h"

struct LightSpotShader : renderer::Shader
{
	gui::Color color = gui::Color(255);

	std::tuple<vec3, vec3, vec3> vertex(const Face& face, int idx) override;

	gui::Color fragment(const vec2i& uv, const vec3& bar) override;

	LightSpotShader* clone(void* memory);

	int size();
};
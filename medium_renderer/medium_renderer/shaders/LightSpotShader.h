#pragma once

#include "../SoftwareRenderer/shader/shader.h"
#include "../SoftwareRenderer/geometry/geometry.h"

struct LightSpotShader : renderer::Shader
{
	float Intensity = 1.0f;

	std::tuple<vec3, vec3, vec3> vertex(const vec3& vert, const vec3& norm, int idx) override;

	gui::Color fragment(const vec2i& uv, const vec3& bar) override;

	LightSpotShader* clone(void* memory);

	int size();

};


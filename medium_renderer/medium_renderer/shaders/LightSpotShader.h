#pragma once

#include "../SoftwareRenderer/shader/shader.h"
#include "../SoftwareRenderer/geometry/geometry.h"

struct LightSpotShader : renderer::Shader
{
	float Intensity = 1.0f;

	std::tuple<gm::vec3, gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx) override;

	gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) override;

	LightSpotShader* clone(void* memory);

	int size();

};


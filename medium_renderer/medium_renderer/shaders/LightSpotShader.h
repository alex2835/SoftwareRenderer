#pragma once

#include "../SoftwareRenderer/shader/shader.h"
#include "../SoftwareRenderer/geometry/geometry.h"

struct LightSpotShader : renderer::Shader
{
	gm::mat4 Transforms;
	float Intensity = 1.0f;

	std::tuple<gm::vec3, bool> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx);

	gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar);

	LightSpotShader* clone(char* memory);

	int size();

};


#pragma once

#include "../SoftwareRenderer/include.h"


struct GuroShader : renderer::Shader
{
	vec3 CameraPos;
	vec3 LightPos;
	vec3 LightStrengt;

	std::tuple<vec3, vec3, vec3>
		vertex(const vec3& vert, const vec3& norm, int idx) override;
	
	gui::Color
		fragment(const vec2i& uv, const vec3& bar) override;

	GuroShader* clone(void* memory) override;
	int size() override;
};

#pragma once

#include "../SoftwareRenderer/include.h"


struct GuroShader : renderer::Shader
{
	gui::Image* diffuse;

	gm::vec3 LightPos;
	gm::vec3 LightStrengt;

	std::tuple<gm::vec3, gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx) override;

	gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) override;

	
	GuroShader* clone(void* memory) override;
	
	int size() override;

};

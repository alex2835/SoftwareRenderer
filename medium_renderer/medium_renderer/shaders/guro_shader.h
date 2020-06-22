#pragma once

#include "../SoftwareRenderer/include.h"


struct GuroShader : renderer::Shader
{
	gui::Image* diffuse;

	gm::mat4 Model;
	gm::mat4 View;
	gm::mat4 Projection;

	//gm::mat4 Transforms;

	std::tuple<gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm) override;

	gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) override;
};

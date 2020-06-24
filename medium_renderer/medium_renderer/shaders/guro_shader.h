#pragma once

#include "../SoftwareRenderer/include.h"


struct GuroShader : renderer::Shader
{
	gui::Image* diffuse;

	gm::mat4 Model;
	gm::mat4 View;
	gm::mat4 Projection;

	gm::vec3 CameraPos;
	gm::vec3 LightPos;
	gm::vec3 LightStrengt;

	gm::mat4 Transforms;

	std::tuple<gm::vec3, gm::vec3, gm::vec3> vertex(const gm::vec3& vert, const gm::vec3& norm, int idx) override;

	gui::Color fragment(const gm::vec2i& uv, const gm::vec3& bar) override;


	void set_model(const gm::mat4& model);
	void set_view(const gm::mat4& view);
	void set_projection(const gm::mat4& projection);


	GuroShader* clone(char* memory) override;

	int size() override;

};

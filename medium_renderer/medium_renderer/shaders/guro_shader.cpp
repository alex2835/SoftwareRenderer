
#include "guro_shader.h"



std::tuple<gm::vec3, gm::vec3> GuroShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{
	gm::vec3 vert_out = (Projection * View * Model * gm::mat4(vert)).toVec3();

	//gm::vec3 norm_out = (((Projection * View * Model).get_transposed() * gm::mat4(vert))).toVec3();
	//gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	//gm::vec3 norm_out = (Transforms.get_transposed() * gm::mat4(norm)).toVec3();

	LightStrengt[idx] = __max(LightDir * norm.get_normalized(), 0.1f);

	return { vert_out , norm };
}

gui::Color GuroShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	float intensity = LightStrengt * bar;
	return diffuse->get_pixel(uv.x, uv.y) * intensity;
 }


#include "guro_shader.h"



std::tuple<gm::vec3, gm::vec3> GuroShader::vertex(const gm::vec3& vert, const gm::vec3& norm)
{
	gm::vec3 vert_out = (Projection * View * Model * gm::mat4(vert)).toVec3();
	//gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	//gm::vec3 norm_out = (Transforms.get_transposed() * gm::mat4(norm)).toVec3();

	return { vert_out , norm };
}

gui::Color GuroShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	return diffuse->get_pixel(uv.x, uv.y);
}

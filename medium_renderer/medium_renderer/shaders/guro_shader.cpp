
#include "guro_shader.h"



std::tuple<gm::vec3, bool> GuroShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{

	gm::vec3 vert_out = (Projection * View * Model * gm::mat4(vert)).toVec3();

	//gm::vec3 norm_out = (((Projection * View * Model).get_transposed() * gm::mat4(vert))).toVec3();
	//gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	//gm::vec3 norm_out = (Transforms.get_transposed() * gm::mat4(norm)).toVec3();

	// light intensity
	LightStrengt[idx] = __max(LightDir * norm.get_normalized(), 0.1f);

	// backface culling
	bool discard = (CameraPos - vert).normalize() * norm < 0.0f;

	return { vert_out , discard };
}

gui::Color GuroShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	float intensity = LightStrengt * bar;
	return diffuse->get_pixel(uv.x, uv.y) * intensity;
 }


GuroShader* GuroShader::clone()
{
	return new GuroShader(*this);
}


int GuroShader::size()
{
	return sizeof(GuroShader);
}

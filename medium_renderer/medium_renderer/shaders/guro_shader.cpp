
#include "guro_shader.h"


std::tuple<gm::vec3, gm::vec3, gm::vec3> GuroShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{
	gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	gm::vec3 global_pos = (Model * gm::mat4(vert)).toVec3();
	gm::vec3 normal =  (ModelIT * gm::mat4(norm)).toVec3_direct().normalize();

	// attenuation
	float distance = (LightPos - vert).norm();
	float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));

	// light intensity
	LightStrengt[idx] = __max((LightPos - Model.get_col(3)).get_normalized() * norm.get_normalized(), 0.1f) * attenuation;

	
	return { vert_out , global_pos, normal};
}

gui::Color GuroShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	float intensity = LightStrengt * bar;
	return diffuse->get_pixel(uv.x, uv.y) * intensity;
 }


GuroShader* GuroShader::clone(void* memory)
{
	return new(memory) GuroShader(*this);
}


int GuroShader::size()
{
	return sizeof(GuroShader);
}

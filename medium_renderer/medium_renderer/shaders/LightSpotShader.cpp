
#include "LightSpotShader.h"


std::tuple<gm::vec3, gm::vec3, gm::vec3> LightSpotShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{
	gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	gm::vec3 global_pos = (Model * gm::mat4(vert)).toVec3();
	gm::vec3 normal = (ModelT * gm::mat4(norm)).toVec3_direct().normalize();

	return { vert_out, global_pos, normal };
}


gui::Color LightSpotShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	return gui::Color(255 * Intensity);
}


LightSpotShader* LightSpotShader::clone(void* memory)
{
	return new(memory) LightSpotShader(*this);
}


int LightSpotShader::size()
{
	return sizeof(LightSpotShader);
}

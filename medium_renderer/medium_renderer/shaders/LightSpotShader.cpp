
#include "LightSpotShader.h"


std::tuple<gm::vec3, bool> LightSpotShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{
	gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	return { vert_out, false };
}


gui::Color LightSpotShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	return gui::Color(255 * Intensity);
}


LightSpotShader* LightSpotShader::clone(char* memory)
{
	return new LightSpotShader(*this);
}


int LightSpotShader::size()
{
	return sizeof(LightSpotShader);
}

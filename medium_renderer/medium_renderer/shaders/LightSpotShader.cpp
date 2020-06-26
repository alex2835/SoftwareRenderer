
#include "LightSpotShader.h"


std::tuple<vec3, vec3, vec3> LightSpotShader::vertex(const Face& face, int idx)
{
	const vec3& vert = face[idx].vert;
	const vec3& norm = face[idx].norm;

	vec3 vert_out = (Transforms * mat4(vert)).toVec3();
	vec3 global_pos = (Model * mat4(vert)).toVec3();
	vec3 normal = normalize((ModelIT * mat4(norm)).toVec3_direct());

	return { vert_out, global_pos, normal };
}


gui::Color LightSpotShader::fragment(const vec2i& uv, const vec3& bar)
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

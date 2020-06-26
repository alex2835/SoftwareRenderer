
#include "guro_shader.h"


std::tuple<vec3, vec3, vec3>
	GuroShader::vertex(const vec3& vert, const vec3& norm, int idx)
	{
		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 normal =  (ModelIT * mat4(norm)).toVec3_direct().normalize();
	
		// attenuation
		float distance = (LightPos - vert).norm();
		float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));
	
		// diffuse intensity
		LightStrengt[idx] = __max((LightPos - Model.get_col(3)).get_normalized() * norm.get_normalized(), 0.1f) * attenuation;

		// specular intensity
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 lightDir = normalize(LightPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);
		
		float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32) * 0.1f;
		
		LightStrengt[idx] = min(spec + LightStrengt[idx], 1.0f);
		
		return { vert_out , global_pos, normal};
	}

gui::Color GuroShader::fragment(const vec2i& uv, const vec3& bar)
{
	float intensity = LightStrengt * bar;
	return diffusemap->get_pixel(uv.x, uv.y) * intensity;
 }


GuroShader* GuroShader::clone(void* memory)
{
	return new(memory) GuroShader(*this);
}


int GuroShader::size()
{
	return sizeof(GuroShader);
}

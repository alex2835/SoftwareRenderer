
#include "guro_shader.h"


std::tuple<vec3, vec3, vec3>
	GuroShader::vertex(const Face& face, int idx)
	{
		const vec3& vert = face[idx].vert;
		const vec3& norm = face[idx].norm;
		const vec2& uv = face[idx].uv;

		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 norm_out = normalize((ModelIT * mat4(norm)).toVec3_direct());
	
		// attenuation
		float distance = length(LightPos - vert);
		float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));
	
		// diffuse and ambient light intensity
		LightStrengt[idx] = __max(normalize(LightPos - global_pos) * norm_out, ambient) * attenuation;

		// specular intensity
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 lightDir = normalize(LightPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);

		// specular only coef
		float spec = pow(__max(dot(viewDir, reflectDir), 0.0f), shanest) * specular;
		
		// combine diffuse specular and ambient
		LightStrengt[idx] = __min(spec + LightStrengt[idx], 1.0f);

		return { vert_out , global_pos, norm_out };
	}

gui::Color GuroShader::fragment(const vec2i& uv, const vec3& bar)
{
	// diffuse map or coef
	gui::Color diffuse_color;
	if (diffuse_flag)
		diffuse_color = diffusemap->get_pixel(uv.x, uv.y);
	else
		diffuse_color = diffuse;

	float intensity = __min(LightStrengt * bar, 1.0f);
	return diffuse_color * intensity;
 }


GuroShader* GuroShader::clone(void* memory)
{
	return new(memory) GuroShader(*this);
}


int GuroShader::size()
{
	return sizeof(GuroShader);
}

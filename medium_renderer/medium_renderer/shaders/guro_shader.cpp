
#include "guro_shader.h"


std::tuple<vec3, vec3, vec3>
	GuroShader::vertex(const Face& face, int idx)
	{
		vec3 vert = face[idx].vert;
		vec3 norm = face[idx].norm;


		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 norm_out = normalize((ModelIT * mat4(norm)).toVec3_direct());
	
		// attenuation
		float distance = length(LightPos - vert);
		float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));
	
		// diffuse and ambient intensity
		LightStrengt[idx] = __max(normalize(LightPos - global_pos) * norm_out, 0.1f) * attenuation;

		// specular intensity
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 lightDir = normalize(LightPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);

		float specular_coef;
		if (specular_flag)
			specular_coef = specularmap->get_pixel(1, 1).r;
		else
			specular_coef = specular;


		float spec = pow(__max(dot(viewDir, reflectDir), 0.0f), 32) * specular;
		
		LightStrengt[idx] = __min(spec + LightStrengt[idx], 1.0f);

		//verts[idx] = vert_out;
		//norms[idx] = norm_out;
		
		return { vert_out , global_pos, norm_out };
	}

gui::Color GuroShader::fragment(const vec2i& uv, const vec3& bar)
{
	// very hight cost
	
	// interpolate
	//vec3 vert = normalize(verts[0] * bar[0] + verts[1] * bar[1] + verts[2] * bar[2]);
	//vec3 norm = normalize(norms[0] * bar[0] + norms[1] * bar[1] + norms[2] * bar[2]);
	//
	//// specular intensity
	//vec3 viewDir = normalize(CameraPos - vert);
	//vec3 lightDir = normalize(LightPos - vert);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64) * 0.1f;
	
	float intensity = __min(LightStrengt * bar, 1.0f);
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

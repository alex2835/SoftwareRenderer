
#include "guro_shader.h"


namespace shaders
{
	using namespace renderer;

	static float calculate_pointLight(const Light& lighter,
		const Material& material,
		const vec3& vert,
		const vec3& global_pos,
		const vec3& norm,
		const vec3& norm_out,
		const vec3& CameraPos)
	{
		// attenuation
		float distance = length(lighter.position - vert);
		float attenuation = 1.0f / (1.0f + lighter.linear * distance + lighter.quadratic * (distance * distance));

		// diffuse and ambient light intensity
		float diffuse = __max(normalize(lighter.position - global_pos) * norm_out, material.ambient) * attenuation;

		// specular intensity
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 lightDir = normalize(lighter.position - vert);
		vec3 reflectDir = reflect(-lightDir, norm);

		// specular only coef
		float spec = pow(__max(dot(viewDir, reflectDir), 0.0f), material.shininess) * material.specular;

		return __min((spec + diffuse) * lighter.intensity, 1.0f);
	}


	static float caclulate_DirLight(const Light& lighter,
		const Material& material,
		const vec3& vert,
		const vec3& global_pos,
		const vec3& norm,
		const vec3& norm_out,
		const vec3& CameraPos)
	{
		vec3 lightDir = normalize(lighter.direction);
		float diffuse = __max(dot(norm, lightDir), material.ambient);

		// specular
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(__max(dot(viewDir, reflectDir), 0.0), material.shininess);

		return __min((diffuse + spec) * lighter.intensity, 1.0f);
	}



	std::tuple<vec3, vec3, vec3>
		GuroShader::vertex(const Face& face, int idx)
	{
		const vec3& vert = face[idx].vert;
		const vec3& norm = face[idx].norm;

		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 norm_out = normalize((ModelIT * mat4(norm)).toVec3_direct());

		LightStrengt[idx] = 0.0f;
		for (int i = 0; i < nLighters; i++)
		{
			switch (lighters[i].type)
			{
			case LightType::DirLight:
				LightStrengt[idx] += caclulate_DirLight(lighters[i], material, vert, global_pos, norm, norm_out, CameraPos);
				break;
			case LightType::PointLight:
				LightStrengt[idx] += calculate_pointLight(lighters[i], material, vert, global_pos, norm, norm_out, CameraPos);
				break;
			}
		}

		LightStrengt[idx] = __min(LightStrengt[idx], 1.0f);
		return { vert_out , global_pos, norm_out };
	}

	gui::Color GuroShader::fragment(const vec2i& uv, const vec3& bar)
	{
		// diffuse map or coef
		gui::Color diffuse_color;
		if (material.diffuse_flag)
			diffuse_color = material.diffusemap->get_pixel(uv.x, uv.y);
		else
			diffuse_color = material.diffuse;

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
}
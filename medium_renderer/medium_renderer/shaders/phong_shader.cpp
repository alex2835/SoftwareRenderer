
#include "phong_shader.h"


namespace shaders
{
	using namespace renderer;

	static float calculate_pointLight(const Light& lighter,
		const Material& material,
		const vec3& vert,
		const vec3& global_pos,
		const vec3& norm,
		const vec3& norm_out,
		const vec3& CameraPos,
		const vec2i& uv)
	{

		vec3 lightDir = normalize(lighter.direction);
		vec3 viewDir = normalize(CameraPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);

		// specular map or coef
		float specular_coef;
		if (material.specular_flag)
			specular_coef = material.specularmap->get_pixel(uv.x, uv.y).r;
		else
			specular_coef = material.specular;

		// specular only coef
		float spec = 0;// pow(__max(dot(viewDir, reflectDir), 0.0f), material.shininess)* specular_coef;

		return __min(spec * lighter.intensity, 1.0f);
	}


	static float caclulate_DirLight(const Light& lighter,
		const Material& material,
		const vec3& vert,
		const vec3& global_pos,
		const vec3& norm,
		const vec3& norm_out,
		const vec3& CameraPos,
		const vec2i& uv)
	{
		vec3 lightDir = normalize(lighter.direction);
		float diffuse = __max(dot(norm, lightDir), material.ambient);

		vec3 viewDir = normalize(CameraPos - vert);
		vec3 reflectDir = reflect(-lightDir, norm);
		
		// specular map or coef
		float specular_coef;
		if (material.specular_flag)
			specular_coef = material.specularmap->get_pixel(uv.x, uv.y).r;
		else
			specular_coef = material.specular;
		
		return pow(__max(dot(viewDir, reflectDir), 0.0f), material.shininess) * specular_coef;
	}



	
	std::tuple<vec3, vec3, vec3>
		PhongShader::vertex(const Face& face, int idx)
	{
		const vec3& vert = face[idx].vert;
		const vec3& norm = face[idx].norm;
		const vec2& uv = face[idx].uv;

		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 norm_out = normalize((ModelIT * mat4(norm)).toVec3_direct());

		
		LightStrengt[idx] = 0.0f;
		for (int i = 0; i < nLighters; i++)
		{
			switch (lighters[i].type)
			{
				case LightType::DirLight:
				{
					// attenuation
					float distance = length(lighters[0].position - vert);
					float attenuation = 1.0f / (1.0f + lighters[0].linear * distance + lighters[0].quadratic * (distance * distance));

					// diffuse and ambient light intensity
					LightStrengt[idx] += __max(normalize(lighters[0].position - global_pos) * norm_out, material.ambient) * attenuation;
					break;
				}
				case LightType::PointLight:
				{
					LightStrengt[idx] += __max((lighters[i].direction - global_pos) * norm_out, material.ambient);
					break;
				}
			}
		}



		verts[idx] = vert_out;
		norms[idx] = norm_out;

		return { vert_out , global_pos, norm_out };
	}

	gui::Color PhongShader::fragment(const vec2i& uv, const vec3& bar)
	{
		// very hight cost

		// interpolate
		vec3 vert = normalize(verts[0] * bar[0] + verts[1] * bar[1] + verts[2] * bar[2]);
		vec3 norm = normalize(norms[0] * bar[0] + norms[1] * bar[1] + norms[2] * bar[2]);

		vec3 global_pos = global_poss[0] * bar[0] + global_poss[1] * bar[1] + global_poss[2] * bar[2];
		vec3 norm_out = normalize(norms_out[0] * bar[0] + norms_out[1] * bar[1] + norms_out[2] * bar[2]);


		//// diffuse map or coef
		gui::Color diffuse_color;
		if (material.diffuse_flag)
			diffuse_color = material.diffusemap->get_pixel(uv.x, uv.y);
		else
			diffuse_color = material.diffuse;
		
		float spec = 0.0f;
		for (int i = 0; i < nLighters; i++)
		{
			switch (lighters[i].type)
			{
			case LightType::DirLight:
			{
				spec += caclulate_DirLight(lighters[i], material, vert, global_pos, norm, norm_out, CameraPos, uv);
				break;
			}
			case LightType::PointLight:
			{
				spec += calculate_pointLight(lighters[i], material, vert, global_pos, norm, norm_out, CameraPos, uv);
				break;
			}
			}
		}

		float intensity = __min(LightStrengt * bar + spec, 1.0f);
		return diffuse_color * intensity;
	}


	PhongShader* PhongShader::clone(void* memory)
	{
		return new(memory) PhongShader(*this);
	}


	int PhongShader::size()
	{
		return sizeof(PhongShader);
	}
}
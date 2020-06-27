
#include "phong_shader.h"


namespace shaders
{
	using namespace renderer;

	std::tuple<vec3, vec3, vec3>
		PhongShader::vertex(const Face& face, int idx)
	{
		const vec3& vert = face[idx].vert;
		const vec3& norm = face[idx].norm;
		const vec2& uv = face[idx].uv;

		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 norm_out = normalize((ModelIT * mat4(norm)).toVec3_direct());

		// attenuation
		float distance = length(lighters[0].position - vert);
		float attenuation = 1.0f / (1.0f + lighters[0].linear * distance + lighters[0].quadratic * (distance * distance));

		// diffuse and ambient light intensity
		LightStrengt[idx] = __max(normalize(lighters[0].position - global_pos) * norm_out, material.ambient) * attenuation;


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

		// diffuse map or coef
		gui::Color diffuse_color;
		if (material.diffuse_flag)
			diffuse_color = material.diffusemap->get_pixel(uv.x, uv.y);
		else
			diffuse_color = material.diffuse;

		vec3 viewDir = normalize(CameraPos - vert);
		vec3 lightDir = normalize(lighters[0].position - vert);
		vec3 reflectDir = reflect(-lightDir, norm);

		// specular map or coef
		float specular_coef;
		if (material.specular_flag)
			specular_coef = material.specularmap->get_pixel(uv.x, uv.y).r;
		else
			specular_coef = material.specular;

		float spec = pow(__max(dot(viewDir, reflectDir), 0.0f), material.shininess) * specular_coef;

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
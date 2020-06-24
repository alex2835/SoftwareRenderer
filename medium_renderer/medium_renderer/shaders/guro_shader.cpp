
#include "guro_shader.h"


std::tuple<gm::vec3, gm::vec3, gm::vec3> GuroShader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
{

	gm::vec3 vert_out = (Transforms * gm::mat4(vert)).toVec3();
	gm::vec3 global_pos = ((View * Model)* gm::mat4(vert)).toVec3();
	gm::vec3 normal = (Model.get_inversed() * gm::mat4(norm)).toVec3();

	// light intensity
	LightStrengt[idx] = __max((LightPos - Model.get_col(3)).get_normalized() * norm.get_normalized(), 0.1f);


	return { vert_out , global_pos, normal};
}

gui::Color GuroShader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
{
	float intensity = LightStrengt * bar;
	return diffuse->get_pixel(uv.x, uv.y) * intensity;
 }


void GuroShader::set_model(const gm::mat4& model)
{
	Model = model;
	Transforms = Projection * View * Model;
}

void GuroShader::set_view(const gm::mat4& view)
{
	View = view;
	Transforms = Projection * View * Model;
}

void GuroShader::set_projection(const gm::mat4& projection)
{
	Projection = projection;
	Transforms = Projection * View * Model;
}


GuroShader* GuroShader::clone(char* memory)
{
	return new(memory) GuroShader(*this);
}


int GuroShader::size()
{
	return sizeof(GuroShader);
}


#include "light_shader.h"

namespace shaders
{
	using namespace renderer;

	std::tuple<vec3, vec3, vec3> lightSpot_shader::vertex(const Face& face, int idx)
	{
		const vec3& vert = face[idx].vert;
		const vec3& norm = face[idx].norm;

		vec3 vert_out = (Transforms * mat4(vert)).toVec3();
		vec3 global_pos = (Model * mat4(vert)).toVec3();
		vec3 normal = normalize((ModelIT * mat4(norm)).toVec3_direct());

		return { vert_out, global_pos, normal };
	}


	gui::Color lightSpot_shader::fragment(const vec2i& uv, const vec3& bar)
	{
		return color;
	}


	lightSpot_shader* lightSpot_shader::clone(void* memory)
	{
		return new(memory) lightSpot_shader(*this);
	}


	int lightSpot_shader::size()
	{
		return sizeof(lightSpot_shader);
	}
}
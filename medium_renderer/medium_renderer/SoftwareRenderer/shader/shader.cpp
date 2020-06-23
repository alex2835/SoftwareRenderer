
#include "shader.h"

namespace renderer
{

	std::tuple<gm::vec3, gm::vec3> Shader::vertex(const gm::vec3& vert, const gm::vec3& norm, int idx)
	{
		return { gm::vec3(), gm::vec3() };
	}

	// output: final color
	gui::Color Shader::fragment(const gm::vec2i& uv, const gm::vec3& bar)
	{
		return gui::Color(255);
	}

}
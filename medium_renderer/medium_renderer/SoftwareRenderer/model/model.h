#pragma once

#include "mesh.h"
#include "../shader/shader.h"
#include "../renderer/renderer.h"

namespace renderer
{
	struct Model
	{
		std::vector<Mesh> meshes;

		void draw_model(Shader* shader);
	};
}
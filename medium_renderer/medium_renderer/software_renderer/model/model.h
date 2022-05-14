#pragma once

#include <filesystem>
#include <locale>
#include <codecvt>

#include "mesh.h"
#include "../shader/shader.h"

namespace renderer
{
	struct Model
	{
		Shader& shader;
		std::vector<Mesh> meshes;

		gm::vec3 position;
		gm::vec3 scale;
		gm::vec3 rotation;

		// name of directory with model and maps
		Model() = default;
		Model(const char* dirname, 
				Shader& shader,
				const gm::vec3& pos = gm::vec3(),
				const gm::vec3& scale = gm::vec3(1.0f));

		bool valid();
	};
}
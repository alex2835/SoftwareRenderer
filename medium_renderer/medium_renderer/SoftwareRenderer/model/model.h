#pragma once

#include <filesystem>
#include <locale>
#include <codecvt>

#include "mesh.h"
#include "../shader/shader.h"
#include "../renderer/renderer.h"

namespace renderer
{
	struct Model
	{
		std::vector<Mesh> meshes;

		gm::vec3 position;
		gm::vec3 scale;
		gm::vec3 rotation;
		
		gm::vec3 CameraPos;

		// name of directory with model and maps
		Model(const char* dirname, const gm::vec3& pos = gm::vec3(), const gm::vec3& scale = gm::vec3(1.0f));

		bool valid();

		void draw(Shader* shader);
	};
}
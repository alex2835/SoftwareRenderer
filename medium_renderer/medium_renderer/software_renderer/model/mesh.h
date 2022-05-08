#pragma once

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "face.h"
#include "../geometry/geometry.h"
#include "image/image.h"


namespace renderer
{

	struct Mesh
	{
		int verts_size = 0;
		int uvs_size = 0;
		int normals_size = 0;

		// faces
		std::vector<Face> faces;

		// maps
		gui::Image diffusemap;
		gui::fImage specularmap;
		gui::fImage normalmap;

		Mesh() = default;
		Mesh(const std::string& filename);

		bool valid();

		int faces_size();

		Face& get_face(int i);

		gui::Color& get_diffuse(const gm::vec2i& uv);
	};

}
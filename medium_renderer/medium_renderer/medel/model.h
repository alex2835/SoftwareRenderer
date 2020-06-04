#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../geometry/geometry.h"
#include "image/image.h"


namespace renderer
{

	struct Model
	{

		std::vector<gm::vec3> verts;
		std::vector<std::vector<gm::vec3i>> faces; // this means vertex/uv/normal
		std::vector<gm::vec3> norms;
		std::vector<gm::vec2> uv;

		// maps
		gui::Image diffusemap;


		Model(const std::string& filename);


		int verts_size();

		int faces_size();

		std::vector<int> face(int idx);

		gm::vec3& get_vert(int i);

		gui::Color& get_diffuse(gm::vec2i& uv);

		gm::vec2i git_uv(int iface, int nvert);
	};

}
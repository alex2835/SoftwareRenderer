#include "model.h"


namespace renderer
{

	Model::Model(const std::string& filename)
	{
		std::ifstream in;
		in.open(filename + ".obj", std::ifstream::in);
		if (in.fail()) return;



		std::string line;

		while (!in.eof()) {

			std::getline(in, line);
			std::istringstream iss(line.c_str());
			char trash;
			
			if (!line.compare(0, 2, "v "))
			{
				iss >> trash;
				gm::vec3 v;
				
				for (int i = 0; i < 3; i++) iss >> v[i];
					verts.push_back(v);
			}
			else if (!line.compare(0, 3, "vn "))
			{
				iss >> trash >> trash;
				gm::vec3 n;

				for (int i = 0; i < 3; i++) iss >> n[i];
					norms.push_back(n);
			}
			else if (!line.compare(0, 3, "vt "))
			{
				iss >> trash >> trash;
				gm::vec2 temp_uv;

				for (int i = 0; i < 2; i++) iss >> temp_uv[i];
					uv.push_back(temp_uv);
			}
			else if (!line.compare(0, 2, "f "))
			{
				std::vector<gm::vec3i> f;
				gm::vec3i tmp;
				iss >> trash;

				while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2])
				{
					for (int i = 0; i < 3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
						f.push_back(tmp);
				}
				faces.push_back(f);
			}
		}

		diffusemap.open((filename + "_diffuse.tga").c_str());
	}


	bool Model::valid()
	{
		return faces.size();
	}


	int Model::verts_size()
	{
		return verts.size();
	}


	int Model::faces_size()
	{
		return faces.size();
	}


	std::vector<int> Model::face(int idx)
	{
		std::vector<int> face;
		for (int i = 0; i < faces[idx].size(); i++)
			face.push_back(faces[idx][i][0]);

		return face;
	}


	gm::vec3& Model::get_vert(int i)
	{
		return verts[i];
	}


	gui::Color& Model::get_diffuse(gm::vec2i& uv)
	{
		return diffusemap[uv.y * diffusemap.width + uv.x];
	}


	gm::vec2i Model::get_uv(int iface, int nvert)
	{
		int idx = faces[iface][nvert][1];
		return gm::vec2i(uv[idx].x * diffusemap.width, uv[idx].y * diffusemap.height);
	}

}
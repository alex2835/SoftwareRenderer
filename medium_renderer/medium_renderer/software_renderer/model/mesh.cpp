
#include "Mesh.h"


namespace renderer
{
	Mesh::Mesh(const std::string& filename)
	{
		std::ifstream in;

		// file input stream
		in.open(filename + ".obj", std::ifstream::in);
		if (in.fail())
			throw std::runtime_error( "invalid path: " + filename );

		// temp stuff
		std::vector<gm::vec3> verts;
		std::vector<std::array<gm::vec3i, 3>> faces; // vec3i means vertex/uv/normal
		std::vector<gm::vec3> norms;
		std::vector<gm::vec2> uv;

		verts.reserve(100);
		faces.reserve(100);
		norms.reserve(100);
		norms.reserve(100);
		uv.reserve(100);

		std::string line;
		while (!in.eof())
		{
			std::getline(in, line);
			std::istringstream iss(line.c_str());
			char trash;

			// verts
			if (!line.compare(0, 2, "v "))
			{
				iss >> trash;
				gm::vec3 v;

				for (int i = 0; i < 3; i++) iss >> v[i];
				verts.push_back(v);
			}
			// normals
			else if (!line.compare(0, 3, "vn "))
			{
				iss >> trash >> trash;
				gm::vec3 n;

				for (int i = 0; i < 3; i++) iss >> n[i];
				norms.push_back(n);
			}
			// uv
			else if (!line.compare(0, 3, "vt "))
			{
				iss >> trash >> trash;
				gm::vec2 temp_uv;

				for (int i = 0; i < 2; i++) iss >> temp_uv[i];
				uv.push_back(temp_uv);
			}
			// face
			else if (!line.compare(0, 2, "f "))
			{
				std::array<gm::vec3i, 3> f;
				gm::vec3i tmp;
				iss >> trash;

				int j = 0;
				while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2])
				{
					for (int i = 0; i < 3; i++)
						tmp[i]--;				// in wavefront obj all indices start at 1, not zero

					f[j++] = tmp;
				}
				faces.push_back(f);
			}
		}

		verts_size = verts.size();
		uvs_size = uv.size();
		normals_size = norms.size();

		// convert to cache friendly struct
		Face res;
		for (int i = 0; i < faces.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res[j].vert = verts[faces[i][j][0]];
				res[j].uv = uv[faces[i][j][1]];
				res[j].norm = norms[faces[i][j][2]];
			}
			this->faces.push_back(res);
		}
		
		// load maps
		diffusemap.open((filename + "_diffuse.jpg").c_str());
		specularmap.open((filename + "_spec.jpg").c_str());
		normalmap.open((filename + "_nm.jpg").c_str());
	}


	bool Mesh::valid()
	{
		return faces.size();
	}

	int Mesh::faces_size()
	{
		return faces.size();
	}

	Face& Mesh::get_face(int i)
	{
		return faces[i];
	}

	gui::Color& Mesh::get_diffuse(const gm::vec2i& uv)
	{
		return diffusemap[uv.y * diffusemap.width + uv.x];
	}

}

#include "model.h"


namespace renderer
{
	 
	Model::Model(const char* dirname, const gm::vec3& pos, const gm::vec3& scale)
		:
		position(pos),
		scale(scale)
	{
		namespace fs = std::filesystem;
		
		for (auto& p : fs::directory_iterator(dirname))
		{
			int str_size = wcslen(p.path().c_str()) + 1;
			std::string filename;
			filename.resize(str_size);

			gui::convert_wchar_to_utf8(filename.data(), str_size, p.path().c_str());
			
			if (filename.find(".obj") != std::string::npos)
			{
				// push mesh
				meshes.emplace_back(filename.substr(0, filename.size() - 5));

				gui::console::printf("%s\n", filename.c_str());
			}

		}

	}

	bool Model::valid()
	{
		bool valid = true;
		for (Mesh& mesh : meshes)
			valid &= mesh.valid();

		return valid && meshes.size();
	}

	void Model::draw(Shader* shader)
	{
		gm::mat4 Scale;
		gm::mat4 Rotation;
		gm::mat4 Translation;

		Scale.set_scale(scale);
		//Rtotaion.set
		Translation.set_col(3, position);
		
		gm::mat4 Model = Translation * Rotation * Scale;
		shader->set_model(Model);

		for (Mesh& mesh : meshes)
		{
			shader->material.set_diffusemap(&mesh.diffusemap);
			shader->material.set_specularmap(&mesh.specularmap);
			shader->material.set_normalmap(&mesh.normalmap);
			shader->material.set_ambient(0.1f);
			
			render_mesh(mesh, shader);
		}
	}
}
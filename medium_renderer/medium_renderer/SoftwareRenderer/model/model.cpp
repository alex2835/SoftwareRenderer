
#include "model.h"


namespace renderer
{
	void Model::draw_model(Shader* shader)
	{
		for (Mesh& mesh : meshes)
		{
			//for (int i = 0; i < 3; i++)
			//	shader->maps[i] = &mesh.maps[i];
			
			render_mesh(mesh, shader);
		}
	}
}
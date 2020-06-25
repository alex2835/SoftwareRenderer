
#include "shader.h"


namespace renderer
{

	void Shader::set_model(const gm::mat4& model)
	{
		Model = model;
		ModelIT = model.get_inversed().get_transposed();
		Transforms = Projection * View * Model;
	}

	void Shader::set_view(const gm::mat4& view)
	{
		View = view;
		Transforms = Projection * View * Model;
	}

	void Shader::set_projection(const gm::mat4& projection)
	{
		Projection = projection;
		Transforms = Projection * View * Model;
	}

}

#include "renderer.h"


namespace renderer
{

Renderer::Renderer(gui::Image_base<uint8_t>& ctx)
	: mContext( ctx ),
	  mCamera( gm::vec3(0, 5, 15), 90, 20 )
{
	UpdateRenderer();
}

void Renderer::RenderModel(Model& model)
{
	Shader& shader = model.shader;

	gm::mat4 scale_mat;
	gm::mat4 rotation_mat;
	gm::mat4 translation_mat;

	scale_mat.set_scale(model.scale);
	translation_mat.set_col(3, model.position);

	gm::mat4 model_mat = translation_mat * rotation_mat * scale_mat;
	shader.set_model(model_mat);

	shader.CameraPos = mCamera.Position;
	shader.set_view(mCamera.get_lookat());
	shader.set_projection(mCamera.get_projection(mContext.width, mContext.height));

	shader.nLighters = mLighters.size();
	for (int i = 0; i < mLighters.size(); i++)
		shader.lighters[i] = mLighters[i];

	for (const Mesh &mesh : model.meshes)
	{
		shader.material.set_diffusemap(&mesh.diffusemap);
		shader.material.set_specularmap(&mesh.specularmap);
		shader.material.set_normalmap(&mesh.normalmap);
		shader.material.set_ambient(0.1f);

		RenderMesh(mesh, shader);
	}
}

void Renderer::RenderMesh(const Mesh& mesh, Shader& in_shader)
{
	// Split whole mesh on tasks
	// and put them on thread pool
	const int tasks = (std::min)(128, mesh.faces_size());

	// reallocate memory for shaders
	if (mShadersBuffer.size() < in_shader.size() * tasks)
		mShadersBuffer.resize(in_shader.size() * tasks);

	// Get actual viewport
	gm::mat4 ViewPort = gm::get_viewport(mContext.width, mContext.height);

	std::vector<std::future<void>> futures(tasks);
	for (int i = 0; i < tasks; i++)
	{
		int from = i * mesh.faces_size() / tasks;
		int to = (i + 1) * mesh.faces_size() / tasks;

		futures[i] = gui::thread_pool.add_task(
			[&, from, to, id = i]()
			{
				// Create copy for this thread (No memory allocation)
				Shader* shader = in_shader.clone(mShadersBuffer.data() + in_shader.size() * id);

				for (int i = from; i < to; i++)
				{
					bool fit = false;
					bool cull = false;

					gm::vec2i uv[3];
					gm::vec3 screen_coords[3];
					const Face& face = mesh.get_face(i);

					for (int j = 0; j < 3; j++)
					{
						// get uv
						uv[j] = gm::vec2i(mesh.diffusemap.width * face[j].uv.x,
							mesh.diffusemap.height * face[j].uv.y);

						// Vertex shader
						auto [vertex, global, normal] = shader->vertex(face, j);

						// backface culling
						global -= mCamera.Position;
						cull = (mCamera.Position - global).normalize() * normal < -0.1f;

						// clip
						if (vertex.z > 5.0f && vertex.z < 6.0f)
							fit = true;

						// view port
						screen_coords[j] = (ViewPort * gm::mat4(vertex)).toVec3();
					}

					// Draw triangle
					if (fit && !cull) {
						rasterizer::triangle(mContext, screen_coords, uv, mZbuffer.data(), shader);
					}
				}
			}
		);
	}
	for (int i = 0; i < tasks; i++)
		futures[i].get();
}

void Renderer::UpdateRenderer()
{
	if (mZbuffer.size() < mContext.whole_size)
		mZbuffer.resize(mContext.whole_size);

	memset(mZbuffer.data(), 0, mZbuffer.size() * sizeof(float));
	gui::cpu::draw_filled_rect_async(mContext, 0.0f, 0.0f, 1.0f, 1.0f, gui::Color{0, 0, 0});

	for( auto& model : mModels )
		RenderModel( model );
}

}
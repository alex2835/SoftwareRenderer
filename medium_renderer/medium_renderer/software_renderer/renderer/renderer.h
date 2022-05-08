#pragma once

#pragma once
#include <cstring>
#include "image/Image_base.h"
#include "image/draw.h"

#include "../rasterizer/rasterizer.h"
#include "../model/model.h"
#include "../shader/shader.h"
#include "../camera/camera.h"

#include "libs/time.h"
#include "io/input.h"

#include "io/log.h"

namespace renderer
{

class Renerer
{
public:
	Renerer(gui::Image_base<uint8_t>& ctx, gm::vec3& camera);
	void RenderModel(Model& model, Shader& in_shader);
	void RenderMesh(Mesh& mesh, Shader& shader);
	void UpdateRenderer();

private:
	gui::Image_base<uint8_t>& mContext;

	// zbuffer
	std::vector<float> mZbuffer;
	// shaders memory
	std::vector<char> mShadersBuffer;
	// Backface culling
	gm::vec3& mCamera;
};

}


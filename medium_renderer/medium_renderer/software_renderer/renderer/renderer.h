#pragma once

#pragma once
#include <cstring>
#include "image/Image_base.h"
#include "image/draw.h"

#include "../rasterizer/rasterizer.h"
#include "../model/model.h"
#include "../shader/shader.h"
#include "../camera/camera.h"
#include "../light/lighter.h"

#include "libs/time.h"
#include "io/input.h"

#include "io/log.h"

namespace renderer
{

class Renderer
{
public:
	Renderer(gui::Image_base<uint8_t>& ctx);
	void UpdateRenderer();

	auto& GetCamera() { return mCamera; }
	auto& GetLighters() { return mLighters; }
	auto& GetModels() { return mModels; }

private:
	void RenderModel(Model& model);
	void RenderMesh(const Mesh& mesh, Shader& shader);
	
	gui::Image_base<uint8_t>& mContext;
	std::vector<float> mZbuffer;
	std::vector<char> mShadersBuffer;
	Camera mCamera;
	std::vector<Model> mModels;
	std::vector<Light> mLighters;
	
};

}


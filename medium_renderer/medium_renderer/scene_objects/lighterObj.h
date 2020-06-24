#pragma once

#include "../SoftwareRenderer/geometry/geometry.h"
#include "../SoftwareRenderer/medel/model.h"


struct LighterObj : renderer::Model
{
	gm::vec3 Position;
	float scale = 1.0f;
	float intensity = 1.0f;

	LighterObj() = default;

	LighterObj(renderer::Model model,
		    const gm::vec3& position = gm::vec3(),
		    float scale = 1.0f,
		    float intensity = 1.0f);

};
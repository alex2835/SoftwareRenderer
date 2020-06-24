#pragma once

#include "../SoftwareRenderer/geometry/geometry.h"
#include "../SoftwareRenderer/medel/model.h"


struct Lighter : renderer::Model
{
	gm::vec3 Position;
	float scale = 1.0f;
	float intensity = 1.0f;

	Lighter() = default;

	Lighter(renderer::Model model, 
		    const gm::vec3& position = gm::vec3(),
		    float scale = 1.0f,
		    float intensity = 1.0f);

};
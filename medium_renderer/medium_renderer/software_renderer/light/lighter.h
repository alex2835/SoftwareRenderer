#pragma once

#include "../geometry/geometry.h"
#include "../model/mesh.h"


struct LighterObj
{
	gm::vec3 Position;
	float scale = 1.0f;
	float intensity = 1.0f;
	renderer::Mesh* mesh;

	LighterObj() = default;

	LighterObj(renderer::Mesh* mesh,
		    const gm::vec3& position = gm::vec3(),
		    float scale = 1.0f,
		    float intensity = 1.0f);

};
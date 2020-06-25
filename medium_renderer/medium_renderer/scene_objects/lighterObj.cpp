
#include "lighterObj.h"


LighterObj::LighterObj(renderer::Mesh* mesh,
				 const gm::vec3& position, 
				 float scale,
				 float intensity)
	:
	mesh(mesh),
	scale(scale),
	Position(position),
	intensity(intensity)
{}

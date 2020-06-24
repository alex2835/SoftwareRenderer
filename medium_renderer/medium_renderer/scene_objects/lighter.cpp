
#include "lighter.h"


Lighter::Lighter(renderer::Model model, 
				 const gm::vec3& position, 
				 float scale,
				 float intensity)
	:
	Model(std::move(model)),
	scale(scale),
	Position(position),
	intensity(intensity)
{}

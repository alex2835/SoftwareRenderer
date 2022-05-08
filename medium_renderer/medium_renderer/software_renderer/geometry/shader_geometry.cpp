#include "geometry.h"

namespace gm
{
	vec3 reflect(const vec3& incidentVec, const vec3& normal)
	{
		return incidentVec - normal * 2.0f * (incidentVec * normal);
	}


	vec3 refract(const vec3& incidentVec, const vec3& normal, float eta)
	{
		vec3 out;
		float N_dot_I = normal * incidentVec;
		float k = 1.0f - eta * eta * (1.0f - N_dot_I * N_dot_I);
		if (k < 0.0f)
			out = vec3(0.0f, 0.0f, 0.0f);
		else
			out = incidentVec * eta - normal * (eta * N_dot_I + sqrtf(k));
		return out;
	}

}

#include "geometry.h"

namespace gm
{

	// matrix generation

	mat4 lookat(const vec3& eye, const vec3& center, const vec3& up)
	{
		vec3 z = (eye - center).get_normalized();
		vec3 x = (up ^ z).get_normalized();
		vec3 y = (z ^ x).get_normalized();

		mat4 res;
		for (int i = 0; i < 3; i++) {
			res[0][i] = x[i];
			res[1][i] = y[i];
			res[2][i] = z[i];
			res[i][3] = -center[i];
		}
		return res;
	}


	mat4 viewport(int x, int y, int w, int h, int depth)
	{
		mat4 m;
		m[0][3] = x + w / 2.f;
		m[1][3] = y + h / 2.f;
		m[2][3] = depth / 2.f;

		m[0][0] = w / 2.f;
		m[1][1] = h / 2.f;
		m[2][2] = depth / 2.f;
		return m;
	}

}
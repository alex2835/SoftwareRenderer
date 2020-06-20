
#include "geometry.h"

#ifndef PI
#define PI 3.14159265359f
#endif

namespace gm
{

	// matrix generation

	mat4 lookat(const vec3& from, const vec3& to, const vec3& temp)
	{
		//vec3 z = (from - to).get_normalized();
		//vec3 x = (up ^ z).get_normalized();
		//vec3 y = (z ^ x).get_normalized();
		//
		//mat4 res;
		//for (int i = 0; i < 3; i++) {
		//	res[0][i] = x[i];
		//	res[1][i] = y[i];
		//	res[2][i] = z[i];
		//	res[i][3] = -from[i];
		//}
		//return res;

		//gm::vec3 z = (from - to).normalize();
		//gm::vec3 x = (up ^ z).normalize();
		//gm::vec3 y = (z ^ x).normalize();
		//
		//mat4 Minv;
		//mat4 Tr;
		//
		//for (int i = 0; i < 3; i++) {
		//	Minv[0][i] = x[i];
		//	Minv[1][i] = y[i];
		//	Minv[2][i] = z[i];
		//	Tr[i][3] = -to[i];
		//}
		//
		//return Minv * Tr;

		vec3 z = (from - to).normalize();
		vec3 x = (temp ^ z).normalize();
		vec3 y = (z ^ x).normalize();
		mat4 Minv;
		mat4 Tr;
		for (int i = 0; i < 3; i++) {
			Minv[0][i] = x[i];
			Minv[1][i] = y[i];
			Minv[2][i] = z[i];
			Tr[i][3] = -to[i];
		}
		return Minv * Tr;
		//vec3 forward = (from - to).get_normalized();
		//vec3 right = temp.get_normalized() ^ forward;
		//vec3 up = forward ^ right;
		//
		//mat4 camToWorld;
		//
		//camToWorld[0][0] = right.x;
		//camToWorld[0][1] = right.y;
		//camToWorld[0][2] = right.z;
		//camToWorld[1][0] = up.x;
		//camToWorld[1][1] = up.y;
		//camToWorld[1][2] = up.z;
		//camToWorld[2][0] = forward.x;
		//camToWorld[2][1] = forward.y;
		//camToWorld[2][2] = forward.z;
		//
		//camToWorld[0][3] = -from.x;
		//camToWorld[1][3] = -from.y;
		//camToWorld[2][3] = -from.z;
		//
		//return camToWorld;

	}


	mat4 viewport(int x, int y, int w, int h, int depth)
	{
		mat4 m;
		m[0][3] = x + w / 2.0f;
		m[1][3] = y + h / 2.0f;
		m[2][3] = depth / 2.0f;

		m[0][0] = w / 2.0f;
		m[1][1] = h / 2.0f;
		m[2][2] = depth / 2.0f;
		return m;
	}


	mat4 projection(float angleOfView, float near, float far)
	{
		// set the basic projection matrix
		mat4 M;
		float scale = 1.0f / tanf(angleOfView * 0.5f * PI / 180.0f);
		M[0][0] = scale; // scale the x coordinates of the projected point 
		M[1][1] = scale; // scale the y coordinates of the projected point 
		M[2][2] = -far / (far - near); // used to remap z to [0,1] 
		M[3][2] = -far * near / (far - near); // used to remap z [0,1] 
		M[2][3] = -1; // set w = -z 
		M[3][3] = 0;

		return M;
	}

}
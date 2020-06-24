
#include "geometry.h"


namespace gm
{

	// matrix generation

	mat4 lookat(const vec3& from, const vec3& to, const vec3& temp)
	{
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

	mat4 get_viewport(int width, int height)
	{
		return gm::viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
	}


	// compute screen coordinates first
	static void gluPerspective(
		const float& angleOfView,
		const float& imageAspectRatio,
		const float& n, const float& f,
		float& b, float& t, float& l, float& r)
	{
		float scale = tanf(angleOfView * PI / 360.0f) * n;
		r = imageAspectRatio * scale, l = -r;
		t = scale, b = -t;
	}

	// set the OpenGL perspective projection matrix
	static void glFrustum(
		const float& b, const float& t, const float& l, const float& r,
		const float& n, const float& f,
		mat4& M)
	{
		// set OpenGL perspective projection matrix
		M[0][0] = 2.0f * n / (r - l);
		M[0][1] = 0.0f;
		M[0][2] = 0.0f;
		M[0][3] = 0.0f;

		M[1][0] = 0.0f;
		M[1][1] = 2.0f * n / (t - b);
		M[1][2] = 0.0f;
		M[1][3] = 0.0f;

		M[2][0] = (r + l) / (r - l);
		M[2][1] = (t + b) / (t - b);
		M[2][2] = (f + n) / (f - n);
		M[2][3] = 1.0f;

		M[3][0] = 0.0f;
		M[3][1] = 0.0f;
		M[3][2] = 2.0f * f * n / (f - n);
		M[3][3] = 0.0f;
	}

	mat4 projection(float aspect, float fov, float near, float far)
	{
		mat4 Projection;
		float b, t, l, r;
		gluPerspective(fov, aspect, near, far, b, t, l, r);
		glFrustum(b, t, l, r, near, far, Projection);
		return Projection;
	}

}
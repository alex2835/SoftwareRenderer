
#include "rasterizer.h"


namespace renderer
{
	namespace rasterizer
	{
		
		bool barycentric(const gm::vec3& A, const gm::vec3& B, const gm::vec3& C,
			const gm::vec3i& P, gm::vec3* out)
		{
			gm::vec3 s[2];
			for (int i = 0; i < 2; i++)
			{
				s[i][0] = C[i] - A[i];
				s[i][1] = B[i] - A[i];
				s[i][2] = A[i] - P[i];
			}

			// compute cross product
			gm::vec3 u = s[0] ^ s[1];

			if (std::abs(u[2]) > 0.01f)
			{
				out->x = 1.0f - (u.x + u.y) / u.z;
				out->y = u.y / u.z;
				out->z = u.x / u.z;
				if (out->x >= 0.0f && out->y >= 0.0f && out->z >= 0.0f)
					return true;
			}
			return false;
		}


		void triangle(gui::Image_base<uint8_t>& surface, gm::vec3* pts, gm::vec2i* uv, float* zbuffer, Shader* shader)
		{
			gm::vec2 bot_left((std::numeric_limits<float>::max)(), (std::numeric_limits<float>::max)());
			gm::vec2 top_right((std::numeric_limits<float>::min)(), (std::numeric_limits<float>::min)());

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					bot_left[j] = __max(0.0f, __min(bot_left[j], pts[i][j]));
					if (j == 1)
						top_right[j] = __min(surface.height, __max(top_right[j], pts[i][j]));
					else
						top_right[j] = __min(surface.width, __max(top_right[j], pts[i][j]));
				}
			}

			gm::vec3i P;
			gm::vec3 bar;

			for (P.y = bot_left.y; P.y < top_right.y; P.y++)
			{
				for (P.x = bot_left.x; P.x < top_right.x; P.x++)
				{
					if (barycentric(pts[0], pts[1], pts[2], P, &bar))
					{
						float z = 0.0f;
						for (int i = 0; i < 3; i++)
							z += pts[i][2] * bar[i];

						if (zbuffer[int(P.x + P.y * surface.width)] < z)
						{
							zbuffer[int(P.x + P.y * surface.width)] = z;

							gm::vec2i uvP;
							uvP.x = uv[0].x * bar[0] + uv[1].x * bar[1] + uv[2].x * bar[2];
							uvP.y = uv[0].y * bar[0] + uv[1].y * bar[1] + uv[2].y * bar[2];

							// Fragment shader
							gui::Color color = shader->fragment(uvP, bar);

							surface[P.y * surface.width + P.x] = color;
						}
					}
				}
			}

		}

	}
}
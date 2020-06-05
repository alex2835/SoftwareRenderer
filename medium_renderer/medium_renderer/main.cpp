

#include "window/window.h"
#include "io/log.h"

#include "geometry/geometry.h"


#include "rasterizer/rasterizer.h"
#include "medel/model.h"
//#include "tests/geometry_test.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE no, LPSTR args, int cmdShow)
{
	gui::Window* window = new gui::Window(L"Widnow", 800, 600);
	window->canvas.set_max_buffer_size();

	// zbuffer
	int zbuffer_size = window->canvas.capacity;
	float* zbuffer = new float[zbuffer_size];

	// model
	renderer::Model model("models/african_head_jpg/african_head");

	if (!model.valid())
	{
		gui::console::printf("Error: Can not load model\n");
		return 1;
	}


	// light dir
	gm::vec3 light_dir(0, 0, -1);


	gui::Timer timer(60);
	while (gui::Window::is_running(window))
	{

		// reallocate zbuffer if neccessery
		if (zbuffer_size < window->width() * window->height())
		{
			delete[] zbuffer;
			int zbuffer_size = window->width() * window->height();
			float* zbuffer = new float[zbuffer_size];
		}


		// draw model
		for (int i = 0; i < model.faces_size(); i++)
		{
			std::vector<int> face = model.face(i);
			gm::vec3 screen_coords[3];
			gm::vec3 world_coords[3];
			for (int j = 0; j < 3; j++)
			{
				gm::vec3 v = model.get_vert(face[j]);
				//screen_coords[j] = (ViewPort * Projection * ModelView * Matrix44f(v)).toVec3();
				screen_coords[j] = gm::vec3(v.x * window->width() / 2 + window->width() / 2,
											v.y * window->height() / 2 + window->height() / 2,
											v.z);
				world_coords[j] = v;
			}

			gm::vec3 n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);

			n.normalize();
			float intensity = n * light_dir;

			intensity = intensity < 0 ? 0.1 : intensity;

			gm::vec2i uv[3];
			for (int k = 0; k < 3; k++)
				uv[k] = model.get_uv(i, k);

			renderer::rasterizer::triangle(window->canvas, screen_coords, uv, zbuffer, model, intensity);
		}


		gui::console::printf("fps: %d\n", timer.FPS);

		timer.update();
		window->render_canvas();
		gui::Window::default_msg_proc();
	}

	return 0;
}

 



//Matrix44f lookAt(Vec3f& from, Vec3f& to, Vec3f tmp = Vec3f(0, 1, 0))
//{
//	Vec3f forward = (from - to).normalize();
//	Vec3f right = cross(tmp.normalize(), forward);
//	Vec3f up = cross(forward, right);
//
//	Matrix44f camToWorld(empty);
//
//	camToWorld[0][0] = right.x;
//	camToWorld[0][1] = right.y;
//	camToWorld[0][2] = right.z;
//	camToWorld[1][0] = up.x;
//	camToWorld[1][1] = up.y;
//	camToWorld[1][2] = up.z;
//	camToWorld[2][0] = forward.x;
//	camToWorld[2][1] = forward.y;
//	camToWorld[2][2] = forward.z;
//
//	camToWorld[3][0] = from.x;
//	camToWorld[3][1] = from.y;
//	camToWorld[3][2] = from.z;
//
//	return camToWorld;
//}

//Matrix44f lookAt(Vec3f eye, Vec3f center, Vec3f up = Vec3f(0, 1, 0))
//{
//	Vec3f z = (eye - center).normalize();
//	Vec3f x = cross(up, z).normalize();
//	Vec3f y = cross(z, x).normalize();
//	Matrix44f res = Matrix44f(identity);
//	for (int i = 0; i < 3; i++) {
//		res[0][i] = x[i];
//		res[1][i] = y[i];
//		res[2][i] = z[i];
//		res[i][3] = -center[i];
//	}
//	return res;
//}
//
//Matrix44f viewport(int x, int y, int w, int h) {
//	Matrix44f m(identity);
//	m[0][3] = x + w / 2.f;
//	m[1][3] = y + h / 2.f;
//	m[2][3] = depth / 2.f;
//
//	m[0][0] = w / 2.f;
//	m[1][1] = h / 2.f;
//	m[2][2] = depth / 2.f;
//	return m;
//}




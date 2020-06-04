

#include "guiAlexandrov.h"
#include "geometry/geometry.h"

#include "tests/geometry_test.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE no, LPSTR args, int cmdShow)
{
	//gui::Window* window = new gui::Window(L"Widnow", 800, 600);


	//gui::Window::wait_msg_proc();
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





#include "geometry.h"


namespace gm
{
	// vec2
	template struct Vec2<float>;
	template struct Vec2<int>;

	// vec3
	template struct Vec3<float>;
	template struct Vec3<int>;


	// vec4
	template struct Vec4<float>;
	template struct Vec4<int>;


	// mat3
	template struct Matrix3<int>;
	template struct Matrix3<float>;

	// mat4
	template struct Matrix4<int>;
	template struct Matrix4<float>;

}
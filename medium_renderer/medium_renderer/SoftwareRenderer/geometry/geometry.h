#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>


namespace gm
{

	const float PI = 3.14159265359f;

	// ========================== 2d Vector ==================================

	template <typename T>
	struct Vec2
	{
		union
		{
			struct { T x, y; };
			T raw[2];
		};

		Vec2() : x(0), y(0) {}
		Vec2(T x, T y) : x(x), y(y) {}

		Vec2(const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
		}

		Vec2<T>& operator = (const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}


		Vec2<T>& operator += (const Vec2<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vec2<T>& operator *= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vec2<T> operator + (const Vec2<T>& other) const
		{
			Vec2<T> temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vec2<T> operator * (float scalar) const
		{
			Vec2<T> temp;
			temp.x = x * scalar;
			temp.y = y * scalar;
			return temp;
		}

		// dot product
		float operator * (const Vec2<T>& other) const
		{
			float res = 0;
			for (int i = 0; i < 2; i++)
				res += raw[i] * other[i];

			return res;
		}

		T& operator [] (int inx)
		{
			return raw[inx];
		}


		const T& operator [] (int inx) const
		{
			return raw[inx];
		}

		bool operator == (const Vec2<T>& other) const
		{
			return x == other.x &&
				   y == other.y;
		}

		bool operator != (const Vec2<T>& other) const
		{
			return !(*this == other);
		}

	};

	typedef Vec2<float> vec2;
	typedef Vec2<int> vec2i;

	extern template struct Vec2<float>;
	extern template struct Vec2<int>;


	// ========================= 3d Vector =============================

	template <typename T>
	struct Vec3
	{
		union
		{
			struct { T x, y, z; };
			T raw[3];
		};

		Vec3() : x(0), y(0), z(0) {}
		Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

		Vec3<T>& operator += (const Vec3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vec3<T>& operator -= (const Vec3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vec3<T>& operator *= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vec3<T> operator + (const Vec3<T>& other) const
		{
			Vec3<T> tmp;
			tmp.x = x + other.x;
			tmp.y = y + other.y;
			tmp.z = z + other.z;
			return tmp;
		}

		Vec3<T> operator - (const Vec3<T>& other) const
		{
			Vec3<T> tmp;
			tmp.x = x - other.x;
			tmp.y = y - other.y;
			tmp.z = z - other.z;
			return tmp;
		}

		Vec3<T> operator * (float scalar) const
		{
			Vec3<T> tmp;
			tmp.x = x * scalar;
			tmp.y = y * scalar;
			tmp.z = z * scalar;
			return tmp;
		}


		// dot product
		float operator * (const Vec3<T>& other) const
		{
			float res = 0;
			for (int i = 0; i < 3; i++)
				res += raw[i] * other[i];

			return res;
		}

		// cross product
		Vec3<T> operator^ (const Vec3<T>& other) const
		{
			return Vec3<T>(y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x);
		}


		T& operator [] (int inx)
		{
			return raw[inx];
		}

		const T& operator [] (int inx) const
		{
			return raw[inx];
		}

		float norm() const
		{
			float a = x * x;
			float b = y * y;
			float c = z * z;
			return sqrtf(a + b + c);
		}

		Vec3<T>& normalize()
		{
			*this *= (1.0f / norm());
			return *this;
		}

		Vec3<T> get_normalized() const
		{
			return (*this) * (1.0f / norm());;
		}


		bool operator == (const Vec3<T>& other) const
		{
			return x == other.x &&
				y == other.y &&
				z == other.z;
		}

		bool operator != (const Vec3<T>& other) const
		{
			return !(*this == other);
		}

	};

	typedef Vec3<float> vec3;
	typedef Vec3<int> vec3i;


	extern template struct Vec3<float>;
	extern template struct Vec3<int>;



	// ========================= 4d Vector ================================

	template <typename T>
	struct Vec4
	{
		union
		{
			struct { T x, y, z, w; };
			T raw[4];
		};

		Vec4() : x(0), y(0), z(0), w(0) {}
		Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		Vec4<T>& operator += (const Vec4<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vec4<T>& operator -= (const Vec4<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vec4<T>& operator *= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		Vec4<T> operator + (const Vec4<T>& other) const
		{
			Vec4<T> tmp;
			tmp.x = x + other.x;
			tmp.y = y + other.y;
			tmp.z = z + other.z;
			tmp.w = w + other.w;
			return tmp;
		}

		Vec4<T> operator - (const Vec4<T>& other) const
		{
			Vec4<T> tmp;
			tmp.x = x - other.x;
			tmp.y = y - other.y;
			tmp.z = z - other.z;
			tmp.w = w - other.w;
			return tmp;
		}

		Vec4<T> operator * (float scalar) const
		{
			Vec4<T> tmp;
			tmp.x = x * scalar;
			tmp.y = y * scalar;
			tmp.z = z * scalar;
			tmp.w = w * scalar;
			return tmp;
		}

		// dot product
		float operator * (const Vec4<T>& other) const
		{
			float res = 0;
			for (int i = 0; i < 4; i++)
				res += raw[i] * other[i];

			return res;
		}


		T& operator [] (int inx)
		{
			return raw[inx];
		}

		const T& operator [] (int inx) const
		{
			return raw[inx];
		}


		float norm() const
		{
			float a = x * x;
			float b = y * y;
			float c = z * z;
			float d = w * w;
			return sqrtf(a + b + c + d);
		}

		Vec4<T>& normalize()
		{
			*this *= (1.0f / norm());
			return *this;
		}

		Vec4<T> get_normalized() const
		{
			return (*this) * (1.0f / norm());
		}


		bool operator == (const Vec4<T>& other) const
		{
			return x == other.x &&
				y == other.y &&
				z == other.z &&
				w == other.w;
		}

		bool operator != (const Vec4<T>& other) const
		{
			return !(*this == other);
		}

	};

	typedef Vec4<float> vec4;
	typedef Vec4<int> vec4i;


	extern template struct Vec4<float>;
	extern template struct Vec4<int>;



	// ================================ Matrix 3x3 ======================================

	template<typename T>
	class Matrix3
	{
	public:
		T x[3][3] = { { 1, 0, 0 },
					  { 0, 1, 0 },
					  { 0, 0, 1 } };


		Matrix3() = default;
		Matrix3(T a, T b, T c, T d, T e, T f, T g, T h, T i)
		{
			x[0][0] = a;
			x[0][1] = b;
			x[0][2] = c;
			x[1][0] = d;
			x[1][1] = e;
			x[1][2] = f;
			x[2][0] = g;
			x[2][1] = h;
			x[2][2] = i;
		}


		Matrix3(Vec3<T> v)
		{
			clear();
			x[0][0] = v.x;
			x[1][0] = v.y;
			x[2][0] = v.z;
		}


		const T* operator [] (int i) const { return x[i]; }
		T* operator [] (int i) { return x[i]; }


		// Multiply the current matrix with another matrix
		Matrix3 operator * (const Matrix3& other) const
		{
			Matrix3 tmp;
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					tmp[i][j] = x[i][0] * other.x[0][j] +
						x[i][1] * other.x[1][j] +
						x[i][2] * other.x[2][j];
				}
			}
			return tmp;
		}


		// point-matrix multiplication
		template<typename S>
		Vec3<S> operator * (const Vec3<S>& src) const
		{
			Vec3<S> temp;
			S w;

			temp.x = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0];
			temp.y = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1];
			temp.z = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2];

			return temp;
		}


		Matrix3 get_transposed() const
		{
			Matrix3 t;
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					t[i][j] = x[j][i];
				}
			}
			return t;
		}


		Matrix3 get_inversed()
		{
			int i, j, k;
			Matrix3 s;
			Matrix3 t(*this);

			// Forward elimination
			for (i = 0; i < 3; i++) {
				int pivot = i;

				T pivotsize = t[i][i];

				if (pivotsize < 0)
					pivotsize = -pivotsize;

				for (j = i + 1; j < 3; j++) {
					T tmp = t[j][i];

					if (tmp < 0)
						tmp = -tmp;

					if (tmp > pivotsize) {
						pivot = j;
						pivotsize = tmp;
					}
				}

				if (pivotsize == 0) {
					// Cannot invert singular matrix
					return Matrix3();
				}

				if (pivot != i) {
					for (j = 0; j < 3; j++) {
						T tmp;

						tmp = t[i][j];
						t[i][j] = t[pivot][j];
						t[pivot][j] = tmp;

						tmp = s[i][j];
						s[i][j] = s[pivot][j];
						s[pivot][j] = tmp;
					}
				}

				for (j = i + 1; j < 3; j++) {
					T f = t[j][i] / t[i][i];

					for (k = 0; k < 3; k++) {
						t[j][k] -= f * t[i][k];
						s[j][k] -= f * s[i][k];
					}
				}
			}

			// Backward substitution
			for (i = 2; i >= 0; --i) {
				T f;

				if ((f = t[i][i]) == 0) {
					// Cannot invert singular matrix
					return Matrix3();
				}

				for (j = 0; j < 3; j++) {
					t[i][j] /= f;
					s[i][j] /= f;
				}

				for (j = 0; j < i; j++) {
					f = t[j][i];

					for (k = 0; k < 3; k++) {
						t[j][k] -= f * t[i][k];
						s[j][k] -= f * s[i][k];
					}
				}
			}

			return s;
		}

		Matrix3<T>& inverse()
		{
			*this = get_inversed();
			return *this;
		}


		void clear()
		{
			memset(this, 0, sizeof(Matrix3));
		}

		Vec3<T> toVec3()
		{
			return  Vec3<T>(x[0][0], x[1][0], x[2][0]);
		}

	};

	typedef Matrix3<float> mat3;
	typedef Matrix3<int> mat3i;


	extern template struct Matrix3<int>;
	extern template struct Matrix3<float>;



	// ================================ Matrix 4X4 =======================================

	template<typename T>
	class Matrix4
	{
	public:
		T x[4][4] = { { 1, 0, 0, 0 },
					  { 0, 1, 0, 0 },
					  { 0, 0, 1, 0 },
					  { 0, 0, 0, 1 } };


		Matrix4() = default;
		Matrix4(T a, T b, T c, T d, T e, T f, T g, T h,
			T i, T j, T k, T l, T m, T n, T o, T p)
		{
			x[0][0] = a;
			x[0][1] = b;
			x[0][2] = c;
			x[0][3] = d;
			x[1][0] = e;
			x[1][1] = f;
			x[1][2] = g;
			x[1][3] = h;
			x[2][0] = i;
			x[2][1] = j;
			x[2][2] = k;
			x[2][3] = l;
			x[3][0] = m;
			x[3][1] = n;
			x[3][2] = o;
			x[3][3] = p;
		}

		Matrix4(Vec3<T> v)
		{
			clear();
			x[0][0] = v.x;
			x[1][0] = v.y;
			x[2][0] = v.z;
			x[3][0] = 1.f;
		}


		const T* operator [] (int i) const { return x[i]; }
		T* operator [] (int i) { return x[i]; }


		// Multiply the current matrix with another matrix
		Matrix4 operator * (const Matrix4& other) const
		{
			Matrix4 tmp;
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					tmp[i][j] = x[i][0] * other.x[0][j] + x[i][1] * other.x[1][j] +
						x[i][2] * other.x[2][j] + x[i][3] * other.x[3][j];
				}
			}
			return tmp;
		}


		// point-matrix multiplication
		template<typename S>
		Vec3<S> operator* (const Vec3<S>& src) const
		{
			Vec3<S> temp;
			S w;

			temp.x = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0] + x[3][0];
			temp.y = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1] + x[3][1];
			temp.z = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2] + x[3][2];
			w = src[0] * x[0][3] + src[1] * x[1][3] + src[2] * x[2][3] + x[3][3];

			temp.x /= w;
			temp.y /= w;
			temp.z /= w;

			return temp;
		}


		// vector-matrix multiplication
		template<typename S>
		Vec3<S> multDirMatrix(const Vec3<S>& src) const
		{
			Vec3<S> temp;

			temp.x = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0];
			temp.y = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1];
			temp.z = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2];

			return temp;
		}


		Matrix4 get_transposed() const
		{
			Matrix4 t;
			for (uint8_t i = 0; i < 4; ++i) {
				for (uint8_t j = 0; j < 4; ++j) {
					t[i][j] = x[j][i];
				}
			}
			return t;
		}

		Matrix4 get_inversed()
		{
			int i, j, k;
			Matrix4 s;
			Matrix4 t(*this);

			// Forward elimination
			for (i = 0; i < 3; i++) {
				int pivot = i;

				T pivotsize = t[i][i];

				if (pivotsize < 0)
					pivotsize = -pivotsize;

				for (j = i + 1; j < 4; j++) {
					T tmp = t[j][i];

					if (tmp < 0)
						tmp = -tmp;

					if (tmp > pivotsize) {
						pivot = j;
						pivotsize = tmp;
					}
				}

				if (pivotsize == 0) {
					// Cannot invert singular matrix
					return Matrix4();
				}

				if (pivot != i) {
					for (j = 0; j < 4; j++) {
						T tmp;

						tmp = t[i][j];
						t[i][j] = t[pivot][j];
						t[pivot][j] = tmp;

						tmp = s[i][j];
						s[i][j] = s[pivot][j];
						s[pivot][j] = tmp;
					}
				}

				for (j = i + 1; j < 4; j++) {
					T f = t[j][i] / t[i][i];

					for (k = 0; k < 4; k++) {
						t[j][k] -= f * t[i][k];
						s[j][k] -= f * s[i][k];
					}
				}
			}

			// Backward substitution
			for (i = 3; i >= 0; --i) {
				T f;

				if ((f = t[i][i]) == 0) {
					// Cannot invert singular matrix
					return Matrix4();
				}

				for (j = 0; j < 4; j++) {
					t[i][j] /= f;
					s[i][j] /= f;
				}

				for (j = 0; j < i; j++) {
					f = t[j][i];

					for (k = 0; k < 4; k++) {
						t[j][k] -= f * t[i][k];
						s[j][k] -= f * s[i][k];
					}
				}
			}

			return s;
		}

		Matrix4<T>& inverse()
		{
			*this = get_inversed();
			return *this;
		}

		void clear()
		{
			memset(this, 0, sizeof(Matrix4));
		}

		Vec4<T> toVec4()
		{
			return  Vec4<T>(x[0][0], x[1][0], x[2][0], x[3][0]);
		}

		Vec3<T> toVec3()
		{
			return  Vec3<T>(x[0][0] / x[3][0], x[1][0] / x[3][0], x[2][0] / x[3][0]);
		}
	};

	typedef Matrix4<float> mat4;
	typedef Matrix4<int> mat4i;

	extern template struct Matrix4<int>;
	extern template struct Matrix4<float>;



	// ======================= Matrix generation ===============================

	mat4 lookat(const vec3& eye, const vec3& center, const vec3& up = vec3(0, 1, 0));

	mat4 viewport(int x, int y, int w, int h, int depth = 255);
	mat4 get_viewport(int width, int height);

	mat4 projection(float aspect, float angleOfView, float near, float far);


	inline float radians(float degrees)
	{
		return degrees * 0.01745329251f;
	}

	inline float degrees(float radians)
	{
		return radians * 57.2957795131f;
	}

}
#pragma once

#include "../geometry/geometry.h"
#include <cassert>

inline void geometry_tests()
{

	// vec 3
	gm::vec3 a(1, 2, 3);
	gm::vec3 b(2, 2, 4);
	gm::vec3 c;

	c = a + b;
	assert(c.x == 3 && c.y == 4 && c.z == 7);

	c = a * 3;
	assert(c.x == 3 && c.y == 6 && c.z == 9);

	float dot = a * b;
	assert(18.0f == dot);

	gm::vec3 cross(2, 2, -2);
	assert(cross == (a ^ b));


	// mat 4
	gm::mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 1, 2, 4, 5, 6, 1);
	gm::mat4 transposed = mat.get_transposed();
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			assert(mat[i][j] == transposed[j][i]);
	
	gm::mat4 inverse = mat.get_inversed();


	// mat 3
	gm::mat3 mat_3(1, 2, 3, 4, 1, 2, 3, 8, 9);
	gm::mat3 transposed_3 = mat_3.get_transposed();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			assert(mat[i][j] == transposed[j][i]);

	gm::mat3 inverse_3 = mat_3.get_inversed();

}
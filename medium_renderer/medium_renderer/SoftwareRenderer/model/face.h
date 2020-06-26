#pragma once

#include "../geometry/geometry.h"


struct Vertex
{
	gm::vec3 vert;
	gm::vec3 norm;
	gm::vec2 uv;
};


struct Face
{
	Vertex verts[3];

	inline const Vertex& operator[] (int i) const
	{
		return verts[i];
	}

	inline Vertex& operator[] (int i)
	{
		return verts[i];
	}
};
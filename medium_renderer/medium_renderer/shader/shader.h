#pragma once


namespace renderer
{

	struct Shader
	{

		virtual void vertex() = 0;

		virtual void fragment() = 0;

	};

}
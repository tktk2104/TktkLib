#ifndef VERTEX_2D_SHADER_DATA_H_
#define VERTEX_2D_SHADER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	struct Vertex2dShaderData
	{
		Vector2		pos;
		float		rhw;
		Color		dif;
		Color		spc;
		Vector2		uv;
		Vector2		suv;
	};
}
#endif // !VERTEX_2D_SHADER_DATA_H_
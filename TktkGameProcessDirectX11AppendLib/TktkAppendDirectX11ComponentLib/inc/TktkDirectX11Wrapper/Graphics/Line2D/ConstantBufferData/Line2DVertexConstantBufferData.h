#ifndef LINE_2D_VERTEX_CONSTANT_BUFFER_DATA_H_
#define LINE_2D_VERTEX_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Matrix3.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	struct Line2DVertexConstantBufferData
	{
		float worldMatrix[12];
		Vector2 screenSize;
		float pad2[2];
	};
}
#endif // !LINE_2D_VERTEX_CONSTANT_BUFFER_DATA_H_
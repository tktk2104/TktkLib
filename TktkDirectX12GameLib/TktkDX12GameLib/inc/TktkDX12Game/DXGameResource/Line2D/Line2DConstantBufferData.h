#ifndef LINE_2D_CONSTANT_BUFFER_DATA_H_
#define LINE_2D_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct Line2DConstantBufferData
	{
		float				worldMatrix[12];
		tktkMath::Color		lineColor;
		tktkMath::Vector2	screenSize;
		float				pad[2];
	};
}
#endif // !LINE_2D_CONSTANT_BUFFER_DATA_H_
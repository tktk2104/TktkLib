#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct SpriteMaterialDrawFuncArgs
	{
		unsigned int		viewportId;
		unsigned int		scissorRectId;
		unsigned int		rtvDescriptorHeapId;
		tktkMath::Matrix3	worldMatrix;
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
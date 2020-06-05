#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct SpriteMaterialInitParam
	{
		unsigned int		createDescriptorHeapId;
		unsigned int		useTextureId;
		tktkMath::Color		blendRate		{ 1.0f, 1.0f, 1.0f, 1.0f };;
		tktkMath::Vector2	textureUvOffset	{ 0.0f, 0.0f };
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };
		tktkMath::Vector2	spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_
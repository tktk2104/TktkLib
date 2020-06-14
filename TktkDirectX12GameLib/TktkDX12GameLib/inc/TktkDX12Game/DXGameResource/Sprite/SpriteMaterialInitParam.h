#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/BufferType.h>

namespace tktk
{
	struct SpriteMaterialInitParam
	{
		unsigned int		createDescriptorHeapId;
		BufferType			srvBufferType;
		unsigned int		useBufferId;
		tktkMath::Color		blendRate		{ 1.0f, 1.0f, 1.0f, 1.0f };;
		tktkMath::Vector2	textureUvOffset	{ 0.0f, 0.0f };
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };
		tktkMath::Vector2	spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_
#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

#include <TktkMath/Structs/Matrix3.h>
#include "SpriteMaterialInitParam.h"
#include "SpriteMaterialDrawFuncArgs.h"

namespace tktk
{
	class SpriteMaterialData
	{
	public:

		SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData() = default;

	public:

		void drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// スプライト用の定数バッファを更新する
		void updateSpriteConstantBuffer(const tktkMath::Matrix3& worldMatrix);

	private:

		unsigned int		m_createDescriptorHeapId;
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
		tktkMath::Vector2	m_spriteCenterRate;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_
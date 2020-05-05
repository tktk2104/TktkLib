#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include "SpriteMaterialData.h"
#include "../HeapArray/HeapArray.h"

namespace tktk
{
	class SpriteMaterial
	{
	public:

		SpriteMaterial(unsigned int spriteMaterialNum);
		~SpriteMaterial() = default;

	public:

		void create(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix);

	private:

		HeapArray<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_
#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <memory>
#include "SpriteMaterialData.h"

namespace tktk
{
	class SpriteMaterial
	{
	public:

		SpriteMaterial(unsigned int spriteMaterialNum);
		~SpriteMaterial();

	public:

		void create(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix);

	private:

		std::allocator<SpriteMaterialData> m_allocator;

		unsigned int		m_spriteMaterialNum;
		SpriteMaterialData* m_arrayTopPos;
	};
}
#endif // !SPRITE_MATERIAL_H_
#include "TktkDX12Game/Sprite/SpriteMaterial.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	SpriteMaterial::SpriteMaterial(unsigned int spriteMaterialNum)
		: m_spriteMaterialArray(spriteMaterialNum)
	{
	}

	void SpriteMaterial::create(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_spriteMaterialArray.emplaceAt(id, initParam);
	}

	void SpriteMaterial::drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix)
	{
		auto spritePtr = m_spriteMaterialArray.at(id);

#ifdef _DEBUG
		if (spritePtr == nullptr)
		{
			throw std::runtime_error("not create spriteMaterial");
		}
#endif // _DEBUG

		spritePtr->drawSprite(worldMatrix);
	}
}
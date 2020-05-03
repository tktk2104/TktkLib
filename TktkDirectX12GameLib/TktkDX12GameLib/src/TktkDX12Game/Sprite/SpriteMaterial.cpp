#include "TktkDX12Game/Sprite/SpriteMaterial.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	SpriteMaterial::SpriteMaterial(unsigned int spriteMaterialNum)
		: m_spriteMaterialNum(spriteMaterialNum)
		, m_arrayTopPos(std::allocator_traits<std::allocator<SpriteMaterialData>>::allocate(m_allocator, m_spriteMaterialNum))
	{
	}

	SpriteMaterial::~SpriteMaterial()
	{
		for (unsigned int i = 0; i < m_spriteMaterialNum; i++)
		{
			std::allocator_traits<std::allocator<SpriteMaterialData>>::destroy(m_allocator, m_arrayTopPos + i);
		}

		std::allocator_traits<std::allocator<SpriteMaterialData>>::deallocate(m_allocator, m_arrayTopPos, m_spriteMaterialNum);
	}

	void SpriteMaterial::create(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		std::allocator_traits<std::allocator<SpriteMaterialData>>::construct(m_allocator, m_arrayTopPos + id, initParam);
	}

	void SpriteMaterial::drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix)
	{
#ifdef _DEBUG
		if (id >= m_spriteMaterialNum)
		{
			throw std::out_of_range("out of range");
		}
#endif // _DEBUG

		(*(m_arrayTopPos + id)).drawSprite(worldMatrix);
	}
}
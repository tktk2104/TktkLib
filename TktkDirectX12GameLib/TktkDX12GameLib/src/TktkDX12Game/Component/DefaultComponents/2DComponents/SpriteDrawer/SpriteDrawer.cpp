#include "TktkDX12Game/Component/DefaultComponents/2DComponents/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, int spriteMaterialId)
		: ComponentBase(drawPriority)
		, m_spriteMaterialId(spriteMaterialId)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteDrawer::draw() const
	{
		DX12GameManager::drawSprite(m_spriteMaterialId, m_transform->calculateWorldMatrix());
	}

	void SpriteDrawer::setSpriteMaterialIdImpl(int id)
	{
		m_spriteMaterialId = id;
	}
}
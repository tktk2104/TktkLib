#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawerMaker.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker & SpriteDrawerMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		return m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_textureId
			);
	}

	SpriteDrawerMaker & SpriteDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	void SpriteDrawerMaker::reset()
	{
		m_self.m_drawPriority = 0.0f;
		m_self.m_textureId = 0;
	}
}
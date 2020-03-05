#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawerMaker.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker & SpriteDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = SpriteDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		return m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_textureId,
			m_blendStateId,
			m_blendRate,
			m_depthStencilStateId
			);
	}

	SpriteDrawerMaker & SpriteDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::blendRate(const Color & value)
	{
		m_blendRate = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::textureIdImpl(int value)
	{
		m_textureId = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::blendStateIdImpl(int value)
	{
		m_blendStateId = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::depthStencilStateIdImpl(int value)
	{
		m_depthStencilStateId = value;
		return *this;
	}

	
}
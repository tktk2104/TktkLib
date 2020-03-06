#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingDrawerMaker.h"

namespace tktk
{
	SpriteClippingDrawerMaker SpriteClippingDrawerMaker::m_self;

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = SpriteClippingDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SpriteClippingDrawer> SpriteClippingDrawerMaker::create()
	{
		return m_user->createComponent<SpriteClippingDrawer>(
			m_drawPriority,
			m_textureId,
			m_blendStateId,
			m_depthStencilStateId,
			m_textureClippingLeftTopPos,
			m_textureClippingSize,
			m_textureUvMulRate,
			m_blendRate,
			m_spriteCenterRate
			);
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::textureClippingLeftTopPos(const Vector2 & value)
	{
		m_textureClippingLeftTopPos = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::textureClippingSize(const Vector2 & value)
	{
		m_textureClippingSize = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::textureUvMulRate(const Vector2 & value)
	{
		m_textureUvMulRate = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::blendRate(const Color & value)
	{
		m_blendRate = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::spriteCenterRate(const Vector2 & value)
	{
		m_spriteCenterRate = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::textureIdImpl(int value)
	{
		m_textureId = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::blendStateIdImpl(int value)
	{
		m_blendStateId = value;
		return *this;
	}

	SpriteClippingDrawerMaker & SpriteClippingDrawerMaker::depthStencilStateIdImpl(int value)
	{
		m_depthStencilStateId = value;
		return *this;
	}
}
#include "TktkAppendDxlib2DComponent/Graphics/Sprite/SpriteDrawerMaker.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker & SpriteDrawerMaker::makeStart()
	{
		m_self = SpriteDrawerMaker();
		return m_self;
	}

	std::shared_ptr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		auto spriteDrawer = std::make_shared<SpriteDrawer>(
			m_textureId,
			m_splitTextureIndex,
			m_drawPriority,
			m_spriteCenterPosRate,
			m_blendMode,
			m_blendParam,
			m_reverseFlag,
			m_useClipping,
			m_clippingLeftTopPos,
			m_clippingRightBottomPos
			);

		if (m_useRenderTarget) spriteDrawer->useRenderTarget(m_renderTargetId);

		return spriteDrawer;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::splitTextureIndex(int value)
	{
		m_splitTextureIndex = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::spriteCenterPosRate(const Vector2 & value)
	{
		m_spriteCenterPosRate = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::reverseFlag(ReverseFlag value)
	{
		m_reverseFlag = value;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::useClipping(
		const Vector2 & clippingLeftTopPos,
		const Vector2 & clippingRightBottomPos
	)
	{
		m_useClipping = true;
		m_clippingLeftTopPos = clippingLeftTopPos;
		m_clippingRightBottomPos = clippingRightBottomPos;
		return *this;
	}

	SpriteDrawerMaker & SpriteDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}
#include "TktkAppendDxlib2DComponent/Graphics/Movie/MoviePlayerMaker.h"

namespace tktk
{
	MoviePlayerMaker MoviePlayerMaker::m_self;

	MoviePlayerMaker & MoviePlayerMaker::makeStart(GameObjectPtr user)
	{
		m_self = MoviePlayerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<MoviePlayer> MoviePlayerMaker::create()
	{
		auto spriteDrawer = m_user->createComponent<MoviePlayer>(
			m_drawPriority,
			m_movieId,
			m_movieCenterPosRate,
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

	MoviePlayerMaker & MoviePlayerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::movieId(int value)
	{
		m_movieId = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::movieCenterPosRate(const Vector2 & value)
	{
		m_movieCenterPosRate = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::reverseFlag(ReverseFlag value)
	{
		m_reverseFlag = value;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::useClipping(const Vector2 & clippingLeftTopPos, const Vector2 & clippingRightBottomPos)
	{
		m_useClipping = true;
		m_clippingLeftTopPos = clippingLeftTopPos;
		m_clippingRightBottomPos = clippingRightBottomPos;
		return *this;
	}

	MoviePlayerMaker & MoviePlayerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}
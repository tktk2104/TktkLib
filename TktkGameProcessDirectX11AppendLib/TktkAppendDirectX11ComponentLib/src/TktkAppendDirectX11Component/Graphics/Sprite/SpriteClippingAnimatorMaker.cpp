#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingAnimatorMaker.h"

namespace tktk
{
	SpriteClippingAnimatorMaker SpriteClippingAnimatorMaker::m_self;

	SpriteClippingAnimatorMaker & SpriteClippingAnimatorMaker::makeStart(GameObjectPtr user)
	{
		m_self = SpriteClippingAnimatorMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SpriteClippingAnimator> SpriteClippingAnimatorMaker::create()
	{
		return m_user->createComponent<SpriteClippingAnimator>(
			m_animFrameTextureLeftTopPosArray,
			m_animationIntervalSec,
			m_isLoop,
			m_animSpeedRate
			);
	}

	SpriteClippingAnimatorMaker & SpriteClippingAnimatorMaker::animFrameTextureLeftTopPosArray(const std::vector<Vector2>& value)
	{
		m_animFrameTextureLeftTopPosArray = value;
		return *this;
	}

	SpriteClippingAnimatorMaker & SpriteClippingAnimatorMaker::animationIntervalSec(float value)
	{
		m_animationIntervalSec = value;
		return *this;
	}

	SpriteClippingAnimatorMaker & SpriteClippingAnimatorMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	SpriteClippingAnimatorMaker & SpriteClippingAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}
}
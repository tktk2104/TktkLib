#include "TktkAppendDxlib2DComponent/Graphics/Sprite/SpriteAnimatorMaker.h"

namespace tktk
{
	SpriteAnimatorMaker SpriteAnimatorMaker::m_self;

	SpriteAnimatorMaker & SpriteAnimatorMaker::makeStart(GameObjectPtr user)
	{
		m_self = SpriteAnimatorMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SpriteAnimator> SpriteAnimatorMaker::create()
	{
		return m_user->createComponent<SpriteAnimator>(
			m_textureId,
			m_splitTextureIndexList,
			m_animationIntervalSec,
			m_loop,
			m_animSpeedRate
			);
	}

	SpriteAnimatorMaker & SpriteAnimatorMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	SpriteAnimatorMaker & SpriteAnimatorMaker::animationIntervalSec(float value)
	{
		m_animationIntervalSec = value;
		return *this;
	}

	SpriteAnimatorMaker & SpriteAnimatorMaker::loop(bool value)
	{
		m_loop = value;
		return *this;
	}

	SpriteAnimatorMaker & SpriteAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}
}
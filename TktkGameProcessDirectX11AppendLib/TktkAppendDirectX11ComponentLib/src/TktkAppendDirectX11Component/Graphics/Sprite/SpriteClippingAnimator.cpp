#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingAnimator.h"

#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	SpriteClippingAnimator::SpriteClippingAnimator(
		const std::vector<Vector2>& animationFrameTexturePosArray,
		float animationIntervalSec,
		bool isLoop,
		float animSpeedRate
	)
		: m_animFrameTextureLeftTopPosArray(animationFrameTexturePosArray)
		, m_animationIntervalSec(animationIntervalSec)
		, m_isLoop(isLoop)
		, m_animSpeedRate(animSpeedRate)
	{
		m_animationTotalTime = m_animationIntervalSec * animationFrameTexturePosArray.size();
	}

	void SpriteClippingAnimator::start()
	{
		m_spriteClippingDrawer = getComponent<SpriteClippingDrawer>();

		if (m_spriteClippingDrawer.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteClippingAnimator::update()
	{
		m_animationTimer += (tktk::Time::deltaTime() * m_animSpeedRate);

		if (m_animationTimer > m_animationTotalTime)
			m_animationTimer = (m_isLoop) ? 0.0f : m_animationTotalTime;

		if (m_animationTimer < 0.0f)
			m_animationTimer = (m_isLoop) ? m_animationTotalTime : 0.0f;

		unsigned int curAnimationIdIndex = static_cast<unsigned int>(m_animationTimer / m_animationIntervalSec);

		// •ÛŒ¯
		if (curAnimationIdIndex >= m_animFrameTextureLeftTopPosArray.size()) curAnimationIdIndex = m_animFrameTextureLeftTopPosArray.size() - 1u;

		m_spriteClippingDrawer->setTextureClippingLeftTopPos(m_animFrameTextureLeftTopPosArray.at(curAnimationIdIndex));
	}

	bool SpriteClippingAnimator::isEndAnimation() const
	{
		return (m_animSpeedRate > 0) ? (m_animationTimer >= m_animationTotalTime) : (m_animationTimer <= 0.0f);
	}

	void SpriteClippingAnimator::setAnimFrameTextureLeftTopPosArray(const std::vector<Vector2>& posArray)
	{
		m_animFrameTextureLeftTopPosArray = posArray;
	}

	const std::vector<Vector2>& SpriteClippingAnimator::getAnimFrameTextureLeftTopPosArray() const
	{
		return m_animFrameTextureLeftTopPosArray;
	}

	void SpriteClippingAnimator::setAnimSpeedRate(float animSpeedRate)
	{
		m_animSpeedRate = animSpeedRate;
	}

	float SpriteClippingAnimator::getAnimSpeedRate() const
	{
		return m_animSpeedRate;
	}

	void SpriteClippingAnimator::setIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	bool SpriteClippingAnimator::getIsLoop() const
	{
		return m_isLoop;
	}
}
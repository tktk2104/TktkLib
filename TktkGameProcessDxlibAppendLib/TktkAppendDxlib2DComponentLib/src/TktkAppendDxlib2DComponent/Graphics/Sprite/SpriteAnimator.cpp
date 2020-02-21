#include "TktkAppendDxlib2DComponent/Graphics/Sprite/SpriteAnimator.h"

#include <stdexcept>
#include <algorithm>
#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	SpriteAnimator::SpriteAnimator(
		int textureId,
		const std::vector<int>& splitTextureIndexList,
		float animationIntervalSec,
		bool isLoop,
		float animSpeedRate
	)
		: m_textureId(textureId)
		, m_splitTextureIndexList(splitTextureIndexList)
		, m_animationIntervalSec(animationIntervalSec)
		, m_isLoop(isLoop)
		, m_animSpeedRate(animSpeedRate)
	{
		m_animationTotalTime = m_animationIntervalSec * m_splitTextureIndexList.size();
	}

	void SpriteAnimator::start()
	{
		auto spriteDrawer = getComponent<SpriteDrawer>();

		if (spriteDrawer.isNull())
		{
			throw std::runtime_error("SpriteAnimator not found SpriteDrawer");
		}
		m_spriteDrawer = spriteDrawer;
	}

	void SpriteAnimator::update()
	{
		m_animationTimer += (tktk::Time::deltaTime() * m_animSpeedRate);

		if (m_animationTimer > m_animationTotalTime)
			m_animationTimer = (m_isLoop) ? 0.0f : m_animationTotalTime;

		if (m_animationTimer < 0.0f)
			m_animationTimer = (m_isLoop) ? m_animationTotalTime : 0.0f;

		unsigned int curAnimationIdIndex = static_cast<unsigned int>(m_animationTimer / m_animationIntervalSec);

		// •ÛŒ¯
		if (curAnimationIdIndex >= m_splitTextureIndexList.size()) curAnimationIdIndex = m_splitTextureIndexList.size() - 1u;

		m_spriteDrawer->setTextureId(m_textureId);
		m_spriteDrawer->setSplitTextureIndex(m_splitTextureIndexList.at(curAnimationIdIndex));
	}

	bool SpriteAnimator::isEndAnimation() const
	{
		return (m_animSpeedRate > 0) ? (m_animationTimer >= m_animationTotalTime) : (m_animationTimer <= 0.0f);
	}

	void SpriteAnimator::setTextureId(int textureId)
	{
		m_textureId = textureId;
	}

	int SpriteAnimator::getTextureId() const
	{
		return m_textureId;
	}

	void SpriteAnimator::setSplitTextureIndexList(const std::vector<int>& splitTextureIndexList)
	{
		m_splitTextureIndexList = splitTextureIndexList;

		m_animationTotalTime = m_animationIntervalSec * m_splitTextureIndexList.size();
	}

	const std::vector<int>& SpriteAnimator::getSplitTextureIndexList() const
	{
		return m_splitTextureIndexList;
	}

	void SpriteAnimator::setAnimSpeedRate(float animSpeedRate)
	{
		m_animSpeedRate = animSpeedRate;
	}

	float SpriteAnimator::getAnimSpeedRate() const
	{
		return m_animSpeedRate;
	}

	void SpriteAnimator::setIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	bool SpriteAnimator::getIsLoop() const
	{
		return m_isLoop;
	}
}
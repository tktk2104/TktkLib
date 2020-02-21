#include "TktkAppendDxlib3DComponent/Graphics/Billboard/RectBillboardAnimator.h"

#include <stdexcept>
#include <algorithm>
#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	RectBillboardAnimator::RectBillboardAnimator(
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

	void RectBillboardAnimator::start()
	{
		auto rectBillboardDrawer = getComponent<RectBillboardDrawer>();

		if (rectBillboardDrawer.isNull())
		{
			throw std::runtime_error("RectBillboardAnimator not found RectBillboardDrawer");
		}
		m_rectBillboardDrawer = rectBillboardDrawer;
	}

	void RectBillboardAnimator::update()
	{
		m_animationTimer += (tktk::Time::deltaTime() * m_animSpeedRate);

		if (m_animationTimer > m_animationTotalTime)
			m_animationTimer = (m_isLoop) ? 0.0f : m_animationTotalTime;

		if (m_animationTimer < 0.0f)
			m_animationTimer = (m_isLoop) ? m_animationTotalTime : 0.0f;

		unsigned int curAnimationIdIndex = static_cast<unsigned int>(m_animationTimer / m_animationIntervalSec);

		// •ÛŒ¯
		if (curAnimationIdIndex >= m_splitTextureIndexList.size()) curAnimationIdIndex = m_splitTextureIndexList.size() - 1u;

		m_rectBillboardDrawer->setTextureID(m_textureId);
		m_rectBillboardDrawer->setSplitTextureIndex(m_splitTextureIndexList.at(curAnimationIdIndex));
	}

	bool RectBillboardAnimator::isEndAnimation() const
	{
		return (m_animSpeedRate > 0) ? (m_animationTimer >= m_animationTotalTime) : (m_animationTimer <= 0.0f);
	}

	void RectBillboardAnimator::setTextureId(int textureId)
	{
		m_textureId = textureId;
	}

	int RectBillboardAnimator::getTextureId() const
	{
		return m_textureId;
	}

	void RectBillboardAnimator::setSplitTextureIndexList(const std::vector<int>& splitTextureIndexList)
	{
		m_splitTextureIndexList = splitTextureIndexList;

		m_animationTotalTime = m_animationIntervalSec * m_splitTextureIndexList.size();
	}

	const std::vector<int>& RectBillboardAnimator::getSplitTextureIndexList() const
	{
		return m_splitTextureIndexList;
	}

	void RectBillboardAnimator::setAnimSpeedRate(float animSpeedRate)
	{
		m_animSpeedRate = animSpeedRate;
	}

	float RectBillboardAnimator::getAnimSpeedRate() const
	{
		return m_animSpeedRate;
	}

	void RectBillboardAnimator::setIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	bool RectBillboardAnimator::getIsLoop() const
	{
		return m_isLoop;
	}
}
#include "TktkComponentFramework/Time/ElapsedTimer.h"

#include <cmath>

namespace tktk
{
	ElapsedTimer::ElapsedTimer()
	{
		reset();
	}

	void ElapsedTimer::reset()
	{
		m_preTime = std::clock();
		m_totalTime = 0.0f;
	}

	void ElapsedTimer::update()
	{
		auto curTime = std::clock();
		long timeDist = (curTime - m_preTime);
		m_deltaTime = (static_cast<float>(timeDist) / 1000.0f);
		m_totalTime += deltaTime();
		m_preTime = curTime;
	}

	float ElapsedTimer::deltaTime() const
	{
		return std::fmin(m_deltaTime, m_maximumDeltaTime) * m_timeScaleRate;
	}

	float ElapsedTimer::noScaleDeltaTime() const
	{
		return std::fmin(m_deltaTime, m_maximumDeltaTime);
	}

	float ElapsedTimer::getCurTimeSec()
	{
		return m_totalTime;
	}

	void ElapsedTimer::setMaximumDeltaTime(float maximumDeltaTime)
	{
		m_maximumDeltaTime = std::abs(maximumDeltaTime);
	}

	float ElapsedTimer::getTimeScale()
	{
		return m_timeScaleRate;
	}

	void ElapsedTimer::setTimeScale(float timeScaleRate)
	{
		m_timeScaleRate = std::fmax(0.0f, timeScaleRate);
	}

	float ElapsedTimer::fps()
	{
		return 1.0f / deltaTime();
	}
}
#include "TktkComponentFramework/Time/Time.h"

#include "TktkComponentFramework/Time/TimeManager.h"

namespace tktk
{
	float Time::deltaTime()
	{
		return TimeManager::deltaTime();
	}

	float Time::noScaleDeltaTime()
	{
		return TimeManager::noScaleDeltaTime();
	}

	float Time::getCurTimeSec()
	{
		return TimeManager::getCurTimeSec();
	}

	void Time::setMaximumDeltaTime(float maximumDeltaTime)
	{
		TimeManager::setMaximumDeltaTime(maximumDeltaTime);
	}

	float Time::getTimeScale()
	{
		return TimeManager::getTimeScale();
	}

	void Time::setTimeScale(float timeScaleRate)
	{
		TimeManager::setTimeScale(timeScaleRate);
	}

	int Time::baseFps()
	{
		return TimeManager::getBaseFps();
	}

	float Time::fps()
	{
		return TimeManager::fps();
	}
}
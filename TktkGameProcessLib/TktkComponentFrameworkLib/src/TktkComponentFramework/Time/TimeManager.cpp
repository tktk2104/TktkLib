#include "TktkComponentFramework/Time/TimeManager.h"
#include "TktkComponentFramework/ComponentFrameworkProcessor.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	// 基本となるfps
	int TimeManager::m_baseFps{ 60 };

	// 経過時間のタイマー
	CfpPtr<ElapsedTimer> TimeManager::m_elapsedTimer;

	void TimeManager::initialize()
	{
		m_elapsedTimer = ComponentFrameworkProcessor::createClass<ElapsedTimer>(true);
	}

	void TimeManager::reset()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->reset();
	}

	void TimeManager::update()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->update();
	}

	// 前フレームとの時間の差を求める
	float TimeManager::deltaTime()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->deltaTime();
	}

	// 前フレームとの時間の差を求める（TimeScaleを無視）
	float TimeManager::noScaleDeltaTime()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->noScaleDeltaTime();
	}

	// プログラムが起動してからの時間（秒）を返す
	float TimeManager::getCurTimeSec()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->getCurTimeSec();
	}

	// 最大のdeltaTimeの値を設定（正の数）
	void TimeManager::setMaximumDeltaTime(float maximumDeltaTime)
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->setMaximumDeltaTime(maximumDeltaTime);
	}

	// 時間の経過速度割合を取得する
	float TimeManager::getTimeScale()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->getTimeScale();
	}

	// 時間の経過速度割合を設定する（0.0～float_max）
	void TimeManager::setTimeScale(float timeScaleRate)
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->setTimeScale(timeScaleRate);
	}

	// 基準となるFPSを設定する
	void TimeManager::setBaseFps(int baseFps)
	{
		m_baseFps = baseFps;
	}

	// 基準となるFPSを取得する
	int TimeManager::getBaseFps()
	{
		return m_baseFps;
	}

	// 瞬間的なFPSを取得する
	float TimeManager::fps()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->fps();
	}

#ifdef _DEBUG
	void TimeManager::tempErrorFunc()
	{
		if (m_elapsedTimer.isNull())
		{
			throw std::runtime_error("not found elapsedTimer");
		}
	}
#endif // _DEBUG
}
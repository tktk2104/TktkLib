#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ElapsedTimer.h"

namespace tktk
{
	class TimeManager
	{
	public:

		static void initialize();

		static void reset();

		// 前フレームとの時間の差を求める
		static float deltaTime();

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		static float noScaleDeltaTime();

		// プログラムが起動してからの時間（秒）を返す
		static float getCurTimeSec();

		// 最大のdeltaTimeの値を設定（正の数）
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		static float getTimeScale();

		// 時間の経過速度割合を設定する（0.0～float_max）
		static void setTimeScale(float timeScaleRate);

		// 基準となるFPSを設定する
		static void setBaseFps(int baseFps = 60);

		// 基準となるFPSを取得する
		static int getBaseFps();

		// 瞬間的なFPSを取得する
		static float fps();

#ifdef _DEBUG
	private:
		static void tempErrorFunc();
#endif // _DEBUG

	private:

		// 基本となるfps
		static int m_baseFps;

		// 経過時間のタイマー
		static CfpPtr<ElapsedTimer> m_elapsedTimer;
	};
}

#endif // !TIME_MANAGER_H_
#ifndef TIME_H_
#define TIME_H_

namespace tktk
{
	// 時間管理クラス
	class Time
	{
	public:

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

		// 基準となるFPSを取得する
		static int baseFps();

		// 瞬間的なFPSを取得する
		static float fps();
	};
}
#endif // !TIME_H_
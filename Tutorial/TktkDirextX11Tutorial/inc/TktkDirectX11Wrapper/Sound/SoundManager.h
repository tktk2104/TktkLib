#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "SoundUpdater.h"

namespace tktk
{
	// 「SoundUpdater」に簡単にアクセスするためのクラス
	class SoundManager
	{
	public:

		// 「SoundUpdater」を生成
		static void setUp();

	public:

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		static void load(int id, const std::string& fileName);

		// 指定したサウンドを再生する
		static void play(int id, bool loopPlay);

		// 指定したサウンドを停止する
		static void stop(int id);

		// 指定したサウンドを一時停止する
		static void pause(int id);

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	private:

		static CfpPtr<SoundUpdater> m_updater;
	};
}
#endif // !SOUND_MANAGER_H_
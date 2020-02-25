#ifndef SOUND_UPDATER_H_
#define SOUND_UPDATER_H_

#include <string>
#include <xaudio2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/SoundAssets.h"

namespace tktk
{
	// 「SoundAssets」が持っているサウンドを再生したり止めたりするクラス
	class SoundUpdater
	{
	public:

		SoundUpdater();
		~SoundUpdater();

		SoundUpdater(const SoundUpdater& other) = delete;
		SoundUpdater& operator = (const SoundUpdater& other) = delete;

	public:

		void update();

	public:

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void load(int id, const std::string& fileName);

		// 指定したサウンドを再生する
		void play(int id, bool loopPlay);

		// 指定したサウンドを停止する
		void stop(int id);

		// 指定したサウンドを一時停止する
		void pause(int id);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	public:

		// サウンドアセット
		CfpPtr<SoundAssets> m_assets;

		// サウンドのイベント処理に使用する変数
		HANDLE m_soundEvent{ NULL };

		// XAudioのポインタ
		IXAudio2* m_xAudioPtr{ NULL };

		// マスタリングボイスのポインタ
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_UPDATER_H_

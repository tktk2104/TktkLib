#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <string>
#include <xaudio2.h>
#include "Sound.h"

namespace tktk
{
	class SoundPlayer
	{
	public:

		SoundPlayer(unsigned int soundDataNum);
		~SoundPlayer();

		SoundPlayer(const SoundPlayer& other) = delete;
		SoundPlayer& operator = (const SoundPlayer& other) = delete;

	public:

		void finalize();

		void update();

	public:

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void load(unsigned int id, const std::string& fileName);

		// 指定したサウンドを再生する
		void play(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		void stop(unsigned int id);

		// 指定したサウンドを一時停止する
		void pause(unsigned int id);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	public:

		Sound m_sound;

		// サウンドのイベント処理に使用する変数
		HANDLE m_soundEvent{ NULL };

		// XAudioのポインタ
		IXAudio2* m_xAudioPtr{ NULL };

		// マスタリングボイスのポインタ
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_PLAYER_H_

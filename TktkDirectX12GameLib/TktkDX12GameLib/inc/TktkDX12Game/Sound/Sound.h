#ifndef SOUND_H_
#define SOUND_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SoundData.h"

namespace tktk
{
	// 「SoundData」を管理するクラス
	class Sound
	{
	public:

		Sound(unsigned int soundDataNum);
		~Sound() = default;

		Sound(const Sound& other) = delete;
		Sound& operator = (const Sound& other) = delete;

	public:

		// 新たなサウンドをロードする
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void load(unsigned int id, const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);

		// 全てのサウンドを削除する
		void clear();

		// 指定したサウンドを再生する
		void play(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		void stop(unsigned int id);

		// 指定したサウンドを一時停止する
		void pause(unsigned int id);

		// 再生中のサウンドを更新する
		void updatePlayingSound();

	private:

		HeapArray<SoundData> m_assets;
	};
}
#endif // !SOUND_H_
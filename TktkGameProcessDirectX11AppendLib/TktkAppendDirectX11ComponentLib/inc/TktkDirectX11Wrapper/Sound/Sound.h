#ifndef SOUND_H_
#define SOUND_H_

#include <string>

namespace tktk
{
	// 「SoundManager」の実装の一部を隠すためのクラス
	class Sound
	{
	public:

		// 新しいサウンドを読み込む
		// ※この関数でサウンドを読み込む場合、idは1以上でなければならない
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
	};
}
#endif // !SOUND_H_
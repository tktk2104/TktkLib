#ifndef SOUND_ASSETS_H_
#define SOUND_ASSETS_H_

#include <unordered_map>
#include "SoundData.h"

namespace tktk
{
	// 「SoundData」を管理するクラス
	class SoundAssets
	{
	public:

		SoundAssets() = default;
		~SoundAssets();

		SoundAssets(const SoundAssets& other) = delete;
		SoundAssets& operator = (const SoundAssets& other) = delete;

	public:

		// 新たなサウンドをロードする
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void load(int id, const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);

		// 指定したサウンドを削除する
		void erase(int id);

		// 全てのサウンドを削除する
		void clear();

		// 再生中のサウンドを更新する
		void updatePlayingSound();

		// 指定したサウンドを管理するクラスのポインタを取得
		SoundData* getDataPtr(int id);

	private:

		std::unordered_map<int, SoundData> m_assets;
	};
}
#endif // !SOUND_ASSETS_H_
#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// 新しいサウンドを読み込む（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "SoundId Fraud Type"); }

		// 指定したサウンドを再生する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void play(IdType id, bool loopPlay)
		{
			playImpl(static_cast<int>(id), loopPlay);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void play(IdType id, bool loopPlay) { static_assert(false, "SoundId Fraud Type"); }

		// 指定したサウンドを停止する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void stop(IdType id)
		{
			stopImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void stop(IdType id) { static_assert(false, "SoundId Fraud Type"); }

		// 指定したサウンドを一時停止する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void pause(IdType id)
		{
			pauseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void pause(IdType id) { static_assert(false, "SoundId Fraud Type"); }

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, const std::string& fileName);
		static void playImpl(int id, bool loopPlay);
		static void stopImpl(int id);
		static void pauseImpl(int id);

	private:

		static CfpPtr<SoundUpdater> m_updater;
	};
}
#endif // !SOUND_MANAGER_H_
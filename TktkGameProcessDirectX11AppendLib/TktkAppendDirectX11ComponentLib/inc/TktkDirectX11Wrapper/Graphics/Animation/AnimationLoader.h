#ifndef ANIMATION_LOADER_H_
#define ANIMATION_LOADER_H_

#include <string>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	// アニメーションを読み込む補助クラス
	class AnimationLoader
	{
	public:

		// ボーン名->キーフレーム情報->ボーン名…と整列しているバイナリデータの読み込み専用（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "AnimationId Fraud Type"); }

	private:

		// load()の実装
		static void loadImpl(int id, const std::string& fileName);
	};
}
#endif // !ANIMATION_LOADER_H_
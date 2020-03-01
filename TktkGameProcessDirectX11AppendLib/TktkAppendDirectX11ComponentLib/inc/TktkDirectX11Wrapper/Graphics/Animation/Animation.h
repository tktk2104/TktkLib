#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/AnimationData.h"

namespace tktk
{
	// 「AnimationManager」の実装の一部を隠すためのクラス
	class Animation
	{
	public:

		// 新たなアニメーションをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でアニメーションをロードする場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
		{
			createImpl(static_cast<int>(id), boneKeyFrames);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames) { static_assert(false, "AnimationId Fraud Type"); }

		// 指定したアニメーションを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でアニメーションを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

		// 指定したアニメーションを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const AnimationData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const AnimationData& getData(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		static void eraseImpl(int id);
		static const AnimationData& getDataImpl(int id);
	};
}
#endif // !ANIMATION_H_
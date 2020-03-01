#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/AnimationAssets.h"

namespace tktk
{
	// 「AnimationAssets」に簡単にアクセスするためのクラス
	class AnimationManager
	{
	public:

		// 「AnimationAssets」を生成
		static void setUp();

	public:

		// 新たなアニメーションをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
		{
			createImpl(static_cast<int>(id), boneKeyFrames);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames) { static_assert(false, "AnimationId Fraud Type"); }

		// 指定したアニメーションを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
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

		// 全てのアニメーションを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		static void eraseImpl(int id);
		static const AnimationData& getDataImpl(int id);

	private:

		static CfpPtr<AnimationAssets> m_assetsPtr;
	};
}
#endif // !ANIMATION_MANAGER_H_

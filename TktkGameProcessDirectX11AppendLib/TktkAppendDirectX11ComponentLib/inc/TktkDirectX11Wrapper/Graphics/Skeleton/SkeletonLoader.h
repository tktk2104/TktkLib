#ifndef SKELETON_LOADER_H_
#define SKELETON_LOADER_H_

#include <string>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	// スケルトンを読み込む補助クラス
	class SkeletonLoader
	{
	public:

		// 以下の形式で整列しているバイナリデータの読み込み専用（列挙型を含む整数型のidが渡された場合のみビルド可）
		// 「char[32]name, int id, int parentId, Matrix4 transform, Matrix4 inverse」
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "SkeletonId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, const std::string& fileName);
	};
}
#endif // !SKELETON_LOADER_H_

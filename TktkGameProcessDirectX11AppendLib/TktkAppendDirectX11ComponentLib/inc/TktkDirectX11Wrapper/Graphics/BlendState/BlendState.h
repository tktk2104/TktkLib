#ifndef BLEND_STATE_H_
#define BLEND_STATE_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/BlendStateData.h"
#include "Asset/SystemBlendStateId.h"

namespace tktk
{
	// 「BlendStateManager」の実装の一部を隠すためのクラス
	class BlendState
	{
	public:

		// 新たなブレンドステートを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でブレンドステートを作る場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc)
		{
			createImpl(static_cast<int>(id), blendDesc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc) { static_assert(false, "BlendStateId Fraud Type"); }

		// 指定したブレンドステートを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でブレンドステートを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// 指定したブレンドステートを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id) { static_assert(false, "BlendStateId Fraud Type"); return nullptr; }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const D3D11_BLEND_DESC& blendDesc);
		static void eraseImpl(int id);
		static BlendStateData* getDataPtrImpl(int id);
	};
}
#endif // !BLEND_STATE_H_
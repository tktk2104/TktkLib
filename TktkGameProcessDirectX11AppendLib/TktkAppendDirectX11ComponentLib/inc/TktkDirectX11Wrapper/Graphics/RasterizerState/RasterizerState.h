#ifndef RASTERIZER_STATE_H_
#define RASTERIZER_STATE_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/RasterizerStateData.h"
#include "Asset/SystemRasterizerStateId.h"

namespace tktk
{
	// 「RasterizerStateManager」の実装の一部を隠すためのクラス
	class RasterizerState
	{
	public:

		// 新たなラスタライザステートを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でラスタライザステートを作成する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc)
		{
			createImpl(static_cast<int>(id), desc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// 指定したラスタライザステートを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でラスタライザステートを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// 指定したラスタライザステートを管理するクラスの参照を取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }
	
	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const D3D11_RASTERIZER_DESC& desc);
		static void eraseImpl(int id);
		static const RasterizerStateData& getDataImpl(int id);
	};
}
#endif // !RASTERIZER_STATE_H_

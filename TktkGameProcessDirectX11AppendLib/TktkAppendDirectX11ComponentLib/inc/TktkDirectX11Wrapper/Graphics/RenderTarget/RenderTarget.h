#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/RenderTargetData.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// 「RenderTargetManager」の実装の一部を隠すためのクラス
	class RenderTarget
	{
	public:

		// 新たなレンダーターゲットを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でレンダーターゲットを作る場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture)
		{
			createImpl(static_cast<int>(id), renderTargetTexture);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture) { static_assert(false, "RenderTargetId Fraud Type"); }

		// 指定したレンダーターゲットを削除する
		// ※この関数でレンダーターゲットを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "RenderTargetId Fraud Type"); }

		// 指定したレンダーターゲットを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const RenderTargetData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const RenderTargetData& getData(IdType id) { static_assert(false, "RenderTargetId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, ID3D11Texture2D* renderTargetTexture);
		static void eraseImpl(int id);
		static const RenderTargetData& getDataImpl(int id);
	};
}
#endif // !RENDER_TARGET_H_
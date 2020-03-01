#ifndef RENDER_TARGET_MANAGER_H_
#define RENDER_TARGET_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/RenderTargetAssets.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// 「RenderTargetAssets」に簡単にアクセスするためのクラス
	class RenderTargetManager
	{
	public:

		// 「RenderTargetAssets」を生成
		static void setUp();

	public:

		// 新たなレンダーターゲットを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture)
		{
			createImpl(static_cast<int>(id), renderTargetTexture);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture) { static_assert(false, "RenderTargetId Fraud Type"); }

		// 指定したレンダーターゲットを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
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

		// 全てのレンダーターゲットを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, ID3D11Texture2D* renderTargetTexture);
		static void eraseImpl(int id);
		static const RenderTargetData& getDataImpl(int id);

	private:

		static CfpPtr<RenderTargetAssets> m_assetsPtr;
	};
}
#endif // !RENDER_TARGET_MANAGER_H_
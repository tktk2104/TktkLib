#ifndef DEPTH_STENCIL_STATE_MANAGER_H_
#define DEPTH_STENCIL_STATE_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilStateAssets.h"
#include "Asset/SystemDepthStencilStateId.h"

namespace tktk
{
	class DepthStencilStateManager
	{
	public:

		// 「DepthStencilStateAssets」を生成
		static void setUp();

	public:

		// 新たな深度ステンシルステートを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc)
		{
			createImpl(static_cast<int>(id), depthStencilDesc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// 指定した深度ステンシルステートを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// 指定した深度ステンシルステートを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static DepthStencilStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static DepthStencilStateData* getDataPtr(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// 全ての深度ステンシルステートを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);
		static void eraseImpl(int id);
		static DepthStencilStateData* getDataPtrImpl(int id);

	private:

		static CfpPtr<DepthStencilStateAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_STATE_MANAGER_H_
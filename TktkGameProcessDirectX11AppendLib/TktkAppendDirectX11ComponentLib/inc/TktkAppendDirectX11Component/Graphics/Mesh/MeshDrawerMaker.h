#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	public:

		// インスタンス作成開始
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static MeshDrawerMaker m_self;

	private:

		// プライベートコンストラクタ達
		MeshDrawerMaker() = default;
		MeshDrawerMaker(const MeshDrawerMaker& other) = default;
		MeshDrawerMaker& operator = (const MeshDrawerMaker& other) = default;

	public:

		// 作成する
		CfpPtr<MeshDrawer> create();

		// 描画優先度を設定する
		MeshDrawerMaker& drawPriority(float value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		MeshDrawerMaker& blendRate(const Color& value);

		// カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& cameraId(IdType value)
		{
			return cameraIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		// メッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& meshId(IdType value)
		{
			return meshIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		// スケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& skeltonId(IdType value)
		{
			return skeltonIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& skeltonId(IdType value) { static_assert(false, "SkeltonId Fraud Type"); }

		// マテリアルIDを指定数設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		MeshDrawerMaker& materialIdArray(IdTypes... values)
		{
			return materialIdArrayImpl({static_cast<int>(values)...});
		}
		template <class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		MeshDrawerMaker& materialIdArray(IdTypes... values) { static_assert(false, "MaterialId Fraud Type"); }

		// ブレンドステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// 深度ステンシルステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		MeshDrawerMaker& cameraIdImpl(int value);
		MeshDrawerMaker& meshIdImpl(int value);
		MeshDrawerMaker& skeltonIdImpl(int value);
		MeshDrawerMaker& materialIdArrayImpl(const std::vector<int>& value);
		MeshDrawerMaker& blendStateIdImpl(int value);
		MeshDrawerMaker& depthStencilStateIdImpl(int value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_cameraId{ 0 };
		int m_meshId{ 0 };
		int m_skeltonId{ 0 };
		std::vector<int> m_materialIdArray{ };
		int m_blendStateId{ static_cast<int>(SystemBlendStateId::Basic) };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		int m_depthStencilStateId{ static_cast<int>(SystemDepthStencilStateId::Basic) };
	};
}

#endif // !MESH_DRAWER_MAKER_H_
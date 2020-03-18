#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <array>
#include <vector>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MeshData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/VertexBuffer/VertexBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/IndexBuffer/IndexBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MaterialSlots/Subset.h"

namespace tktk
{
	// メッシュ描画コンポーネント
	// 【必須コンポーネント：Transform3D】
	class MeshDrawer
		: public ComponentBase
	{
	public:

		MeshDrawer(
			float drawPriority,
			int cameraId,
			int meshId,
			int skeltonId,
			const std::vector<int>& materialIdArray,
			int blendStateId,
			const Color& blendRate,
			int depthStencilStateId
		);
		~MeshDrawer() = default;

	public:

		void start();
		void draw() const;

	public:

		const std::array<Matrix4, 256U>& getLocalBoneMatrices() const;

		// ローカルボーン行列を設定する
		void setLocalBoneMatrices(const std::array<Matrix4, 256U>& boneMatrices, unsigned int boneCount);

		// カメラIDを取得する
		int getCameraId() const;

		// カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setCameraId(IdType id)
		{
			setCameraIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setCameraId(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// メッシュIDを取得する
		int getMeshId() const;

		// メッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setMeshId(IdType id)
		{
			setMeshIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setMeshId(IdType id) { static_assert(false, "MeshId Fraud Type"); }

		// スケルトンIDを取得する
		int getSkeltonId() const;

		// スケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setSkeltonId(IdType id)
		{
			setSkeltonIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setSkeltonId(IdType id) { static_assert(false, "SkeltonId Fraud Type"); }

		// マテリアルIDの配列を取得する
		const std::vector<int>& getMaterialIdArray() const;

		// マテリアルIDを指定数設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		void setMaterialIdArray(IdTypes... ids)
		{
			setMaterialIdArrayImpl({ static_cast<int>(ids)... });
		}
		template <class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		void setMaterialIdArray(IdTypes... ids) { static_assert(false, "MaterialId Fraud Type"); }

		// ブレンドステートIDを取得する
		int getBlendStateId() const;

		// ブレンドステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id)
		{
			setBlendStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを取得する
		const Color& getBlendRate() const;

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		void setBlendRate(const Color& rate);

		// 深度ステンシルステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id)
		{
			setDepthStencilStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		void setCameraIdImpl(int id);
		void setMeshIdImpl(int id);
		void setSkeltonIdImpl(int id);
		void setMaterialIdArrayImpl(const std::vector<int>& idArray);
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);

	private:

		// スキニードボーン行列を計算する
		void calculateSkinnedBoneMatrices(std::array<Matrix4, 256U>* result, int skeltonId, const Matrix4& worldMat) const;

		// マテリアルごとに描画を行う
		void drawUseMaterial(unsigned int materialSlot, const MeshData* meshDataPtrt, const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const;

		// メッシュ情報用の定数バッファを更新する
		void updateMeshBuffer(const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const;

		// マテリアル情報用の定数バッファを更新する
		void updateMaterialBuffer(MaterialData* materialDataPtr) const;

		// ライト情報用の定数バッファを更新する
		void updateLightBuffer() const;

	private:

		CfpPtr<Transform3D> m_transform3D;

		std::array<Matrix4, 256U> m_localBoneMatrices;

		int m_cameraId { -1 };
		int m_meshId { -1 };
		int m_skeltonId { -1 };
		std::vector<int> m_materialIdArray;
		int m_blendStateId{ -1 };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		int m_depthStencilStateId{ -1 };
	};
}
#endif // !MESH_DRAWER_H_
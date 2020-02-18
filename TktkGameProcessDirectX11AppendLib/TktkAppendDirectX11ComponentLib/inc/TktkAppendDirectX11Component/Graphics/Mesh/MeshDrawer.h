#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <memory>
#include <array>
#include <vector>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/VertexBuffer/VertexBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/IndexBuffer/IndexBuffer.h"

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
			const std::vector<int>& materialIdArray
		);
		~MeshDrawer();

	public:

		void start();
		void draw() const;

	public:

		int getSkeltonId() const;

		void setLocalBoneMatrices(std::array<Matrix4, 256U> boneMatrices, unsigned int boneCount);

	private:

		void setVertexBuffer(const VertexBuffer& vertexBuffer) const;

		void setIndexBuffer(const IndexBuffer& indexBuffer) const;

		void calculateSkinnedBoneMatrices(std::array<Matrix4, 256U>* result, int skeltonId, const Matrix4& worldMat) const;

		void drawUseMaterial(int materialId, const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const;

		void applyTexture(unsigned int slot, int textureId) const;

		void updateConstantBuffer(int constantBufferId, const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat, MaterialData* materialDataPtr, const std::unordered_map<int, SafetyVoidPtr>& setConstantBufferParamMap) const;

	private:

		CfpPtr<Transform3D> m_transform3D;

		std::array<Matrix4, 256U> m_localBoneMatrices;

		int m_cameraId { -1 };
		int m_meshId { -1 };
		int m_skeltonId { -1 };
		std::vector<int> m_materialIdArray;
	};
}
#endif // !MESH_DRAWER_H_
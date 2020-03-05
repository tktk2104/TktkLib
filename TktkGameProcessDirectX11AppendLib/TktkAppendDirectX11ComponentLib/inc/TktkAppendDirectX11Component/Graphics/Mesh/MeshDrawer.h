#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <array>
#include <vector>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/VertexBuffer/VertexBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/IndexBuffer/IndexBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MaterialSlots/Subset.h"

namespace tktk
{
	// ���b�V���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
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

		int getSkeltonId() const;

		void setLocalBoneMatrices(std::array<Matrix4, 256U> boneMatrices, unsigned int boneCount);

	private:

		void calculateSkinnedBoneMatrices(std::array<Matrix4, 256U>* result, int skeltonId, const Matrix4& worldMat) const;

		// �}�e���A�����Ƃɕ`����s��
		void drawUseMaterial(unsigned int materialSlot, const Subset& subset, const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const;

		// ���b�V�����p�̒萔�o�b�t�@���X�V����
		void updateMeshBuffer(const Matrix4& worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const;

		// �}�e���A�����p�̒萔�o�b�t�@���X�V����
		void updateMaterialBuffer(MaterialData* materialDataPtr) const;

		// ���C�g���p�̒萔�o�b�t�@���X�V����
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
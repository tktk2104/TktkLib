#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <array>
#include <vector>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		const std::array<Matrix4, 256U>& getLocalBoneMatrices() const;

		// ���[�J���{�[���s���ݒ肷��
		void setLocalBoneMatrices(const std::array<Matrix4, 256U>& boneMatrices, unsigned int boneCount);

		// �J����ID���擾����
		int getCameraId() const;

		// �J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setCameraId(IdType id)
		{
			setCameraIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setCameraId(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// ���b�V��ID���擾����
		int getMeshId() const;

		// ���b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setMeshId(IdType id)
		{
			setMeshIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setMeshId(IdType id) { static_assert(false, "MeshId Fraud Type"); }

		// �X�P���g��ID���擾����
		int getSkeltonId() const;

		// �X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setSkeltonId(IdType id)
		{
			setSkeltonIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setSkeltonId(IdType id) { static_assert(false, "SkeltonId Fraud Type"); }

		// �}�e���A��ID�̔z����擾����
		const std::vector<int>& getMaterialIdArray() const;

		// �}�e���A��ID���w�萔�ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		void setMaterialIdArray(IdTypes... ids)
		{
			setMaterialIdArrayImpl({ static_cast<int>(ids)... });
		}
		template <class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		void setMaterialIdArray(IdTypes... ids) { static_assert(false, "MaterialId Fraud Type"); }

		// �u�����h�X�e�[�gID���擾����
		int getBlendStateId() const;

		// �u�����h�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id)
		{
			setBlendStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩���擾����
		const Color& getBlendRate() const;

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		void setBlendRate(const Color& rate);

		// �[�x�X�e���V���X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id)
		{
			setDepthStencilStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		void setCameraIdImpl(int id);
		void setMeshIdImpl(int id);
		void setSkeltonIdImpl(int id);
		void setMaterialIdArrayImpl(const std::vector<int>& idArray);
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);

	private:

		// �X�L�j�[�h�{�[���s����v�Z����
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
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

		// �C���X�^���X�쐬�J�n
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static MeshDrawerMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		MeshDrawerMaker() = default;
		MeshDrawerMaker(const MeshDrawerMaker& other) = default;
		MeshDrawerMaker& operator = (const MeshDrawerMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<MeshDrawer> create();

		// �`��D��x��ݒ肷��
		MeshDrawerMaker& drawPriority(float value);

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		MeshDrawerMaker& blendRate(const Color& value);

		// �J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& cameraId(IdType value)
		{
			return cameraIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		// ���b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& meshId(IdType value)
		{
			return meshIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		// �X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& skeltonId(IdType value)
		{
			return skeltonIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& skeltonId(IdType value) { static_assert(false, "SkeltonId Fraud Type"); }

		// �}�e���A��ID���w�萔�ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		MeshDrawerMaker& materialIdArray(IdTypes... values)
		{
			return materialIdArrayImpl({static_cast<int>(values)...});
		}
		template <class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		MeshDrawerMaker& materialIdArray(IdTypes... values) { static_assert(false, "MaterialId Fraud Type"); }

		// �u�����h�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		MeshDrawerMaker& cameraIdImpl(int value);
		MeshDrawerMaker& meshIdImpl(int value);
		MeshDrawerMaker& skeltonIdImpl(int value);
		MeshDrawerMaker& materialIdArrayImpl(const std::vector<int>& value);
		MeshDrawerMaker& blendStateIdImpl(int value);
		MeshDrawerMaker& depthStencilStateIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
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
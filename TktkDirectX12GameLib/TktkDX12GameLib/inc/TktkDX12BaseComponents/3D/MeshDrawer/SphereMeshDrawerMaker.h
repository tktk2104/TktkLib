#ifndef SPHERE_MESH_DRAWER_MAKER_H_
#define SPHERE_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshDrawer.h"

namespace tktk
{
	// �uSphereMeshDrawer�v�����w���p�[�N���X
	class SphereMeshDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereMeshDrawerMaker() = default;
		SphereMeshDrawerMaker(const SphereMeshDrawerMaker& other) = default;
		SphereMeshDrawerMaker& operator = (const SphereMeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SphereMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereMeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SphereMeshDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& useRtvDescriptorHeapId(IdType value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		SphereMeshDrawerMaker& useRtvDescriptorHeapIdImpl(unsigned int value);
		SphereMeshDrawerMaker& cameraIdImpl(unsigned int value);
		SphereMeshDrawerMaker& shadowMapCameraIdImpl(unsigned int value);
		SphereMeshDrawerMaker& lightIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SphereMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user{  };
		float			m_drawPriority{ 0.0f };
		unsigned int	m_useRtvDescriptorHeapId{  };		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		unsigned int	m_cameraId{ 0U };
		unsigned int	m_shadowMapCameraId{ 0U };
		unsigned int	m_lightId{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !SPHERE_MESH_DRAWER_MAKER_H_
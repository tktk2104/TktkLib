#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshWireFrameDrawer.h"

namespace tktk
{
	// �uSphereMeshWireFrameDrawer�v�����w���p�[�N���X
	class SphereMeshWireFrameDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereMeshWireFrameDrawerMaker() = default;
		SphereMeshWireFrameDrawerMaker(const SphereMeshWireFrameDrawerMaker& other) = default;
		SphereMeshWireFrameDrawerMaker& operator = (const SphereMeshWireFrameDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SphereMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereMeshWireFrameDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SphereMeshWireFrameDrawerMaker& drawPriority(float value);

		// ���a��ݒ肷��
		SphereMeshWireFrameDrawerMaker& radius(float value);

		// �`��F��ݒ肷��
		SphereMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapId(IdType value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& cameraIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& lightIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SphereMeshWireFrameDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user{  };
		float			m_drawPriority{ 0.0f };
		float			m_radius{ 0.5f };
		tktkMath::Color	m_albedoColor{ tktkMath::colorWhite };
		unsigned int	m_useRtvDescriptorHeapId{  };		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		unsigned int	m_cameraId{ 0U };
		unsigned int	m_shadowMapCameraId{ 0U };
		unsigned int	m_lightId{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
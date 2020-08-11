#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	// �uColliderWireFrameDrawer3D�v�̃C���X�^���X���쐬����N���X
	class ColliderWireFrameDrawer3DMaker
	{
	private:  /* �v���C�x�[�g�R���X�g���N�^�B */

		ColliderWireFrameDrawer3DMaker() = default;
		ColliderWireFrameDrawer3DMaker(const ColliderWireFrameDrawer3DMaker& other) = default;
		ColliderWireFrameDrawer3DMaker& operator = (const ColliderWireFrameDrawer3DMaker& other) = default;

	public:

		// �쐬�J�n
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ColliderWireFrameDrawer3D> create();

		// �`��D��x��ݒ肷��
		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapId(IdType value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value);

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private: /* �e��id�w��n�̊֐��̎��� */

		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& cameraIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& shadowMapCameraIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& lightIdImpl(unsigned int value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr				m_user{ };
		float						m_drawPriority{ 0.0f };
		unsigned int				m_cameraId{ 0U };
		unsigned int				m_shadowMapCameraId{ 0U };
		unsigned int				m_lightId{ 0U };
		unsigned int				m_useRtvDescriptorHeapId{  };// �������p�����[�^�̓o�b�N�o�b�t�@�[
		tktkMath::Color				m_lineColor{ tktkMath::colorWhite };
	
	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}

#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
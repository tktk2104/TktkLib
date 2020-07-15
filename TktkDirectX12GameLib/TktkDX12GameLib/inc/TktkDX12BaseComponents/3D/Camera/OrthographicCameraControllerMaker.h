#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "OrthographicCameraController.h"

namespace tktk
{
	// �uOrthographicCameraController�v�����w���p�[�N���X
	class OrthographicCameraControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		OrthographicCameraControllerMaker() = default;
		OrthographicCameraControllerMaker(const OrthographicCameraControllerMaker& other) = default;
		OrthographicCameraControllerMaker& operator = (const OrthographicCameraControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static OrthographicCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<OrthographicCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value);

		// �����J�������͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraWidth(float value);

		// �����J�����c�͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraHeight(float value);

		// �����߃N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraFar(float value);

	private: /* �e��id�w��n�̊֐��̎��� */

		OrthographicCameraControllerMaker& initCameraIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static OrthographicCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user{  };
		unsigned int	m_initCameraId{ 0U };
		float			m_initCameraWidth{ 100.0f };
		float			m_initCameraHeight{ 100.0f };
		float			m_initCameraNear{ 1.0f };
		float			m_initCameraFar{ 100.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraId(IdType value)
	{
		return initCameraIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_
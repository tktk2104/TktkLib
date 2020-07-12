#ifndef BASIC_CAMERA_CONTROLLER_MAKER_H_
#define BASIC_CAMERA_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicCameraController.h"

namespace tktk
{
	// �uBasicCameraController�v�����w���p�[�N���X
	class BasicCameraControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BasicCameraControllerMaker() = default;
		BasicCameraControllerMaker(const BasicCameraControllerMaker& other) = default;
		BasicCameraControllerMaker& operator = (const BasicCameraControllerMaker& other) = default;
	
	public:

		// �쐬�J�n
		static BasicCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicCameraControllerMaker& initCameraId(IdType value);

		// �����J�����ˊp��ݒ肷��
		BasicCameraControllerMaker& initCameraFov(float value);

		// �����J�����A�X�y�N�g���ݒ肷��
		BasicCameraControllerMaker& initCameraAspect(float value);

		// �����߃N���b�v�l��ݒ肷��
		BasicCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		BasicCameraControllerMaker& initCameraFar(float value);

	private: /* �e��id�w��n�̊֐��̎��� */

		BasicCameraControllerMaker& initCameraIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user{  };
		unsigned int	m_initCameraId	{ 0U };
		float			m_initCameraFov		{ 45.0f };
		float			m_initCameraAspect	{};	// �f�t�H���g�̓Q�[���X�N���[���̔䗦
		float			m_initCameraNear	{ 1.0f };
		float			m_initCameraFar		{ 100.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicCameraControllerMaker& initCameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraId(IdType value)
	{
		return initCameraIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !BASIC_CAMERA_CONTROLLER_MAKER_H_
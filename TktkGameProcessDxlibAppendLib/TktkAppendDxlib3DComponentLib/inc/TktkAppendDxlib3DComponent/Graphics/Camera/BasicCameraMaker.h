#ifndef BASIC_CAMERA_MAKER_H_
#define BASIC_CAMERA_MAKER_H_

#include <TktkMath/Vector3.h>
#include "BasicCamera.h"

namespace tktk
{
	// BasicCamera�̃C���X�^���X���쐬����\����
	struct BasicCameraMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static BasicCameraMaker& makeStart();

	public:

		// �쐬����
		BasicCamera* create();

		// �`��D��x
		BasicCameraMaker& drawPriority(float value);

		// �J�����̎ˊp�H��ݒ肷��
		BasicCameraMaker& initCameraFov(float value);

		// �J�����̃A�X�y�N�g���ݒ肷��
		BasicCameraMaker& initCameraAspectRate(float value);

		// �J�������`�悷��ł��߂�������ݒ肷��
		BasicCameraMaker& initCameraDrawingRangeNear(float value);

		// �J�������`�悷��ł�����������ݒ肷��
		BasicCameraMaker& initCameraDrawingRangeFar(float value);

	private:

		// ���g�̃|�C���^
		static BasicCameraMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		float m_initCameraFov{ 45.0f };
		float m_initCameraAspectRate{ 1280.0f / 720.0f };
		float m_initCameraDrawingRangeNear{ 0.1f };
		float m_initCameraDrawingRangeFar{ 1000.0f };
	};
}
#endif // !BASIC_CAMERA_MAKER_H_
#ifndef BASIC_CAMERA_H_
#define BASIC_CAMERA_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class BasicCamera
		: public ComponentBase
	{
	public:

		BasicCamera(
			float drawPriority,					// �`��D��x
			float initCameraFov,				// �J�����̎ˊp�H
			float initCameraAspectRate,			// �J�����̃A�X�y�N�g��
			float initCameraDrawingRangeNear,	// �J�������`�悷��ł��߂�����
			float initCameraDrawingRangeFar		// �J�������`�悷��ł���������
		);

	public:

		// <PolymorphismFunc>
		void afterCollide();
		void draw() const;

	public:

		// �r���[�ϊ��s����v�Z���擾����
		Matrix4 calculateViewMatrix() const;

		// �p�[�X�y�N�e�B�u�ˉe�s����v�Z���擾����
		Matrix4 calculateProjectionMatrix() const;

		// �J�����̎ˊp�H���擾����
		float getCameraFov() const;

		// �J�����̃A�X�y�N�g����擾����
		float getCameraAspectRate() const;

		// �J�������`�悷��ł��߂��������擾����
		float getCameraDrawingRangeNear() const;

		// �J�������`�悷��ł������������擾����
		float getCameraDrawingRangeFar() const;

		// �J�����̎ˊp�H���Đݒ肷��
		void setCameraFov(float cameraFov);

		// �J�����̃A�X�y�N�g����Đݒ肷��
		void setCameraAspectRate(float cameraAspectRate);

		// �J�������`�悷��ł��߂��������Đݒ肷��
		void setCameraDrawingRangeNear(float cameraDrawingRangeNear);

		// �J�������`�悷��ł������������Đݒ肷��
		void setCameraDrawingRangeFar(float cameraDrawingRangeFar);

	private:

		// ���g�̂R�������W�R���|�[�l���g
		std::weak_ptr<Transform3D> m_transform3D;

		// �J�����̎ˊp�H
		float m_cameraFov;

		// �J�����̃A�X�y�N�g��
		float m_cameraAspectRate;

		// �J�������`�悷��ł��߂�����
		float m_cameraDrawingRangeNear;

		// �J�������`�悷��ł���������
		float m_cameraDrawingRangeFar;
	};
}
#endif // !BASIC_CAMERA_H_
#ifndef CAMERA_H_
#define CAMERA_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "CameraData.h"

namespace tktk
{
	// �uCameraData�v���Ǘ�����N���X
	class Camera
	{
	public:

		Camera(unsigned int cameraNum);
		~Camera() = default;

	public:

		// �uCameraData�v�̃C���X�^���X�����
		void create(unsigned int id);

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(unsigned int id) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(unsigned int id, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int id) const;

		// �v�w��̃J�����̃��W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(unsigned int id, const tktkMath::Matrix4& projection);

	private:

		HeapArray<CameraData> m_cameraArray;
	};
}
#endif // !CAMERA_H_
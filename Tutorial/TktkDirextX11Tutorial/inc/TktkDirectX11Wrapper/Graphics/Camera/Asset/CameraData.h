#ifndef CAMERA_DATA_H_
#define CAMERA_DATA_H_

#include <TktkMath/Matrix4.h>

namespace tktk
{
	// �J�������Ǘ�����N���X
	class CameraData
	{
	public:

		CameraData(const Matrix4& viewMatrix, const Matrix4& projectionMatrix);
		~CameraData();

		CameraData(const CameraData& other) = delete;
		CameraData& operator = (const CameraData& other) = delete;

	public:

		// �J�����̃r���[�s��̃|�C���^���擾����
		Matrix4* getViewMatrixPtr();

		// �J�����̃v���W�F�N�V�����s����擾����
		Matrix4* getProjectionMatrixPtr();

	private:

		// �J�����̃r���[�s��
		Matrix4 m_viewMatrix;

		// �J�����̃v���W�F�N�V�����s��
		Matrix4 m_projectionMatrix;
	};
}
#endif // !CAMERA_DATA_H_
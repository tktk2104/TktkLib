#ifndef CAMERA_DATA_H_
#define CAMERA_DATA_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �J���������Ǘ�����N���X
	class CameraData
	{
	public:

		CameraData() = default;
		~CameraData() = default;

	public:

		// �r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix() const;

		// �r���[�s���ݒ肷��
		void setViewMatrix(const tktkMath::Matrix4& view);

		// �v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix() const;

		// �v���W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(const tktkMath::Matrix4& projection);

	private:

		tktkMath::Matrix4 m_viewMatrix			{ tktkMath::Matrix4_v::identity };
		tktkMath::Matrix4 m_projectionMatrix	{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !CAMERA_DATA_H_

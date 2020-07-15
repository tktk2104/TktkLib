#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ���s���˃J��������R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class OrthographicCameraController
		: public ComponentBase
	{
	public:

		OrthographicCameraController(
			unsigned int cameraId,
			float cameraWidth,
			float cameraHeight,
			float cameraNear,
			float cameraFar
		);

	public:

		void start();
		void afterCollide();

	private:

		// �r���[�s��ƃv���W�F�N�V�����s����uTransform3D�v���g���čX�V����
		void updateCameraMat();

	private:

		unsigned int				m_cameraId;
		float						m_cameraWidth;
		float						m_cameraHeight;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
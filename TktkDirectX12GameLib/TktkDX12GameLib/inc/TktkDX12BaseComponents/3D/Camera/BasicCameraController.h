#ifndef BASIC_CAMERA_CONTROLLER_H_
#define BASIC_CAMERA_CONTROLLER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 通常カメラ制御コンポーネント
	// 【必須コンポーネント：Transform3D】
	class BasicCameraController
		: public ComponentBase
	{
	public:

		BasicCameraController(
			unsigned int cameraId,
			float camerafov,
			float cameraAspect,
			float cameraNear,
			float cameraFar
		);

	public:

		void start();
		void afterCollide();

	private:

		// ビュー行列とプロジェクション行列を「Transform3D」を使って更新する
		void updateCameraMat();

	private:

		unsigned int				m_cameraId;
		float						m_cameraFov;
		float						m_cameraAspect;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_CAMERA_CONTROLLER_H_
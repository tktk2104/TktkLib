#ifndef SIMPLE_CAMERA_H_
#define SIMPLE_CAMERA_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class SimpleCamera
		: public ComponentBase
	{
	public:

		SimpleCamera(int cameraId, float cameraFov, float cameraNear, float cameraFar);
		~SimpleCamera();

	public:

		void start();

		void afterCollide();

	public:

		float getCameraFov();
		void setCameraFov(float fov);

		float getCameraNear();
		void setCameraNear(float n);

		float getCameraFar();
		void setCameraFar(float f);

	private:

		CfpPtr<Transform3D> m_transform;

		int m_cameraId;
		float m_cameraFov;
		float m_cameraNear;
		float m_cameraFar;
	};
}
#endif // !SIMPLE_CAMERA_H_

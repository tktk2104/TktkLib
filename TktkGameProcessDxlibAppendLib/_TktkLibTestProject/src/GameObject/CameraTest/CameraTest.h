#ifndef CAMERA_TEST_H_
#define CAMERA_TEST_H_

#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkAppend3DComponent/Transform3DMaker.h>
#include <TktkDxlib2DWrapper/Graphics/Screen/Screen.h>
#include <TktkAppendDxlib3DComponent/Graphics/Camera/BasicCameraMaker.h>
#include "CameraTestScript.h"
#include "SkyTest/SkyTest.h"

class CameraTest
{
public:

	static void create()
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, 100.0f, -300.0f))
			.rotationDeg(Vector3(20.0f, 0.0f, 0.0f))
			//.position(Vector3(0.0f, 300.0f, 0.0f))
			//.rotationDeg(Vector3(89.0f, 0.0f, 0.0f))
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::BasicCameraMaker::makeStart()
			.drawPriority(-100.0f)
			.initCameraFov(45.0f)
			.initCameraAspectRate(tktk::Screen::getGameScreenSize().x / tktk::Screen::getGameScreenSize().y)
			.initCameraDrawingRangeNear(0.1f)
			.initCameraDrawingRangeFar(1000.0f)
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::FirstPersonModuleMaker::makeStart()
			.alwaysMoveForward(true)
			.moveSpeedPerSec(100.0f)
			.rotationDegPerPixelOnMouseMove(0.1f)
			.create()
		);

		gameObject.lock()->addChild(SkyTest::create());

		gameObject.lock()->addComponent(std::make_shared<CameraTestScript>());
	}
};
#endif // !CAMERA_TEST_H_

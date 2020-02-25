#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Camera/SimpleCameraMaker.h>
#include <TktkAppendDirectX11Component/Graphics/Camera/Module/FirstPersonModuleMaker.h>

struct CameraTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(true);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(Vector3(0.0f, 10.0f, -30.0f))
			.create();

		tktk::SimpleCameraMaker::makeStart(gameObject)
			.cameraId(CAMERA_BASIC)
			.cameraFov(45.0f)
			.cameraNear(0.1f)
			.cameraFar(1000.0f)
			.create();

		tktk::FirstPersonModuleMaker::makeStart(gameObject)
			.moveSpeedPerSec(360.0f)
			.rotateDegSpeedPerSec(500.0f)
			.alwaysMoveForward(false)
			.enableUpDownKey(true)
			.create();
	}
};
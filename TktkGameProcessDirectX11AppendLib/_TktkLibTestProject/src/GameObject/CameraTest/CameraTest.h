#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Camera/SimpleCamera.h>
#include <TktkAppendDirectX11Component/Graphics/Camera/Module/FirstPersonModule.h>

struct CameraTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(true);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, 10.0f, -30.0f))
			.create()
		);

		gameObject->createComponent<tktk::SimpleCamera>(
			CAMERA_BASIC,
			45.0f,
			0.1f,
			1000.0f
			);

		gameObject->createComponent<tktk::FirstPersonModule>(
			360.0f,
			200.0f,
			false,
			true
			);
	}
};
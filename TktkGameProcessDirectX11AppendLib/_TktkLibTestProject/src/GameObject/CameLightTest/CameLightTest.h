#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Camera/SimpleCamera.h>
#include <TktkAppendDirectX11Component/Graphics/Light/PointLight.h>
#include <TktkAppendDirectX11Component/Graphics/Camera/Module/FirstPersonModule.h>

struct CameLightTest
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
			500.0f,
			false,
			true
			);

		gameObject->createComponent<tktk::PointLight>(
			1,
			Color(0.5f, 0.5f, 0.5f, 1.0f),
			Color::white,
			Color::white
			);
	}
};
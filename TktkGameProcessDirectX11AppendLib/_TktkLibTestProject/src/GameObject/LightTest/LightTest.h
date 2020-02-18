#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Light/PointLight.h>
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawer.h>
#include "LightTestScript.h"

struct LightTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, 0.0f, -100.0f))
			.scaleRate(Vector3(0.5f))
			.create()
		);

		gameObject->createComponent<tktk::MeshDrawer>(
			0.0f,
			CAMERA_BASIC,
			MESH_ROBOT_KYLE,
			SKELETON_YBot,
			std::vector<int>({ MATERIAL_ROBOT_KYLE })
			);

		gameObject->createComponent<tktk::PointLight>(
			1,
			Color(0.3f, 0.3f, 0.3f, 1.0f),
			Color::white,
			Color::white
			);

		gameObject->createComponent<LightTestScript>();
	}
};
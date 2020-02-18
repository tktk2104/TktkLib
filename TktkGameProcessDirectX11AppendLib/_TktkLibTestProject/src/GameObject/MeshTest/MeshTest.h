#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawer.h>
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimator.h>
#include "MeshTestScript.h"


struct MeshTest
{
	static void create(const Vector3& position)
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(position)
			.create()
		);

		gameObject->createComponent<tktk::MeshDrawer>(
			0.0f,
			CAMERA_BASIC,
			MESH_ROBOT_KYLE,
			SKELETON_YBot,
			std::vector<int>({ MATERIAL_ROBOT_KYLE })
			);

		gameObject->createComponent<tktk::MeshAnimator>(
			tktk::CfpPtr<tktk::MeshDrawer>(),
			ANIMATION_YBot_kicking_1,
			60.0f,
			0.1f
			);

		gameObject->createComponent<MeshTestScript>();
	}
};
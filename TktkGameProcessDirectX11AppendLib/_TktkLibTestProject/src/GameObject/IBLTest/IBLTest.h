#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawer.h>
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimator.h>

struct IBLTest
{
	static void create(const Vector3& position)
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(position)
			.scaleRate(Vector3(0.5f))
			.create()
		);

		gameObject->createComponent<tktk::MeshDrawer>(
			0.0f,
			CAMERA_BASIC,
			MESH_PISTOL,
			-10,
			std::vector<int>({ MATERIAL_IBL_PISTOL })
			);
	}
};
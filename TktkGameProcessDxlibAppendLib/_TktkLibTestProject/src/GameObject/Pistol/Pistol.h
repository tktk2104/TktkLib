#pragma once

#include "CommonIncludePaths.h"

struct Pistol
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, 10.0f, 0.0f))
			.create()
		);

		gameObject->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(1.0f)
			.meshID(MESH_PISTOL)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.meshLocalScale(Vector3(0.1f))
			.create()
		);
	}
};
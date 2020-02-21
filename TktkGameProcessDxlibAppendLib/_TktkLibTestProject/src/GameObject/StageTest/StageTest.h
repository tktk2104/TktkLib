#pragma once

#include "CommonIncludePaths.h"

class StageTest
{
public:

	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, -1.0f, 0.0f))
			.create()
		);

		gameObject->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT)
			.meshID(MeshId::MESH_STAGE)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create()
		);
	}
};
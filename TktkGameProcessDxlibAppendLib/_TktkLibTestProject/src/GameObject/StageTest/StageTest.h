#pragma once

#include "CommonIncludePaths.h"

class StageTest
{
public:

	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(Vector3(0.0f, -1.0f, 0.0f))
			.create();

		tktk::MeshDrawerMaker::makeStart(gameObject)
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT)
			.meshID(MeshId::MESH_STAGE)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create();
	}
};
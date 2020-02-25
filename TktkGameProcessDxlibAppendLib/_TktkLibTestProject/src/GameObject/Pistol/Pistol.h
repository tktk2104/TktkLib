#pragma once

#include "CommonIncludePaths.h"

struct Pistol
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(Vector3(0.0f, 10.0f, 0.0f))
			.create();

		tktk::MeshDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.meshID(MESH_PISTOL)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.meshLocalScale(Vector3(0.1f))
			.create();
	}
};
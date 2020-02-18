#pragma once

#include "CommonIncludePaths.h"

class StageTest
{
public:

	static void create()
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, -1.0f, 0.0f))
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT)
			.meshID(MeshId::MESH_STAGE)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create()
		);
	}
};
#pragma once

#include "CommonIncludePaths.h"

struct Pistol
{
	static void create()
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			.position(Vector3(0.0f, 10.0f, 0.0f))
			.create()
		);

		gameObject.lock()->addComponent(
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
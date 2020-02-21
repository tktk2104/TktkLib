#pragma once

#include "CommonIncludePaths.h"
#include "MeshTestChildScript.h"

struct MeshTestChild
{
	static GameObjectPtr create(const Vector3& pos)
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			//.position(pos)
			.create()
		);

		/*gameObject->addComponent(
			tktk::SphereDrawerMaker::makeStart()
			.sphereColor(Color::red)
			.isFill(true)
			.radius(0.1f)
			.useLight(false)
			.create()
		);*/

		gameObject->addComponent(
			tktk::BoxDrawerMaker::makeStart()
			.boxColor(Color::red)
			.isFill(true)
			.boxSize(Vector3(1.0f))
			.useLight(false)
			.create()
		);

		/*gameObject->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.meshLocalRotation(Quaternion::identity)
			.drawPriority(1.0f)
			.meshID(8)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create()
		);*/

		gameObject->addComponent(new MeshTestChildScript());

		return gameObject;
	}
};
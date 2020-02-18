#pragma once

#include "CommonIncludePaths.h"
#include "MeshTestChildScript.h"

struct MeshTestChild
{
	static tktk::GameObjectPtr create(const Vector3& pos)
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			//.position(pos)
			.create()
		);

		/*gameObject.lock()->addComponent(
			tktk::SphereDrawerMaker::makeStart()
			.sphereColor(Color::red)
			.isFill(true)
			.radius(0.1f)
			.useLight(false)
			.create()
		);*/

		gameObject.lock()->addComponent(
			tktk::BoxDrawerMaker::makeStart()
			.boxColor(Color::red)
			.isFill(true)
			.boxSize(Vector3(1.0f))
			.useLight(false)
			.create()
		);

		/*gameObject.lock()->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.meshLocalRotation(Quaternion::identity)
			.drawPriority(1.0f)
			.meshID(8)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create()
		);*/

		gameObject.lock()->addComponent(std::make_shared<MeshTestChildScript>());

		return gameObject;
	}
};
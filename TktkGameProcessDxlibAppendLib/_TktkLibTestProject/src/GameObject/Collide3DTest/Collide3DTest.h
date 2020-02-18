#pragma once

#include "CommonIncludePaths.h"

struct Collide3DTest
{
	static void create()
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			//.position(Vector3(-80.0f, 0.0f, 0.0f))[x:-0.040122, y:0.884570, z:-0.192970]
			//.scaleRate(Vector3(1.0f, 1.0f, 1.0f))
			.position(Vector3(-0.040122, 0.884570, -0.192970))
			.create()
		);

		/*gameObject.lock()->addComponent(
			tktk::BoxDrawerMaker::makeStart()
			.boxColor(Color::red)
			.isFill(true)
			.boxSize(Vector3(0.1f))
			.useLight(false)
			.create()
		);*/

		/*gameObject.lock()->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(10.0f)
			.meshID(8)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::SphereColliderMaker::makeStart()
			.collisionGroupType(CollisionGroup::COLLISION_GROUP_ENEMY)
			.radius(10.0f)
			.localPosition(Vector3(0.0f, 5.0f, 0.0f))
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::SphereColliderMaker::makeStart()
			.collisionGroupType(CollisionGroup::COLLISION_GROUP_ENEMY)
			.radius(15.0f)
			.localPosition(Vector3(0.0f, 20.0f, 0.0f))
			.create()
		);

		gameObject.lock()->addComponent(
			tktk::Sound3DPlayerMaker::makeStart()
			.playSoundId(SoundId::SOUND_3D_TEST_SE)
			.soundPlayType(tktk::SoundPlayType::SOUND_PLAY_TYPE_LOOP)
			.startToPlay(true)
			.playRadius(100.0f)
			.create()
		);*/

		/*gameObject.lock()->addComponent(
			tktk::BoxColliderMaker::makeStart()
			.collisionGroupType(CollisionGroup::COLLISION_GROUP_ENEMY)
			.boxSize(Vector3(20.0f, 25.0f, 20.0f))
			.localPosition(Vector3(0.0f, 12.5f, 0.0f))
			.create()
		);*/

		/*gameObject.lock()->addComponent(
			tktk::ColliderWireFrameDrawer3DMaker::makeStart()
			.drawPriority(2.0f)
			.wireFrameColor(Color::white)
			.create()
		);*/
	}
};
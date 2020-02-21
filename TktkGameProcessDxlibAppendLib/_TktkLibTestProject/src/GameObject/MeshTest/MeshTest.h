#ifndef MESH_TEST_H_
#define MESH_TEST_H_

#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkAppend3DComponent/Transform3DMaker.h>
#include <TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshDrawerMaker.h>
#include "MeshTestScript.h"

#include "MeshTestChild/MeshTestChild.h"

#include "MeshTestState/MoveState/MeshTestMoveState.h"
#include "MeshTestState/RotateState/MeshTestRotateState.h"
#include "MeshTestState/ScaleState/MeshTestScaleState.h"

struct MeshTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			//.position(Vector3(0.0f, 0.0f, 0.0f))
			.create()
		);

		/*gameObject->addComponent(
			tktk::RectBillboardDrawerMaker::makeStart()
			.drawPriority(10.0f)
			.textureId(TextureId::TEXTURE_ANIM_SAMPLE)
			.splitTextureIndex(0)
			.billboardScaleRate(1.0f)
			.localPos(Vector3(0.0f, 1.5f, 0.0f))
			.create()
		);

		gameObject->addComponent(
			tktk::RectBillboardAnimatorMaker::makeStart()
			.textureId(TextureId::TEXTURE_ANIM_SAMPLE)
			.splitTextureIndexList<0, 1, 2, 3>()
			.animationIntervalSec(0.1f)
			.loop(true)
			.create()
		);*/

		gameObject->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(1.0f)
			.meshID(1)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.meshLocalScale(Vector3(15.0f))
			.meshLocalRotation(Quaternion::identity)
			.create()
		);

		gameObject->addComponent(
			tktk::MeshAnimatorMaker::makeStart()
			.isLoop(true)
			.motionID(4)
			.motionIntervalSec(1.0f / 30.0f)
			.create()
		);

		gameObject->addComponent(
			tktk::BoxColliderMaker::makeStart()
			.collisionGroupType(CollisionGroup::COLLISION_GROUP_PLAYER)
			.boxSize(Vector3(15.0f, 22.0f, 15.0f))
			.localPosition(Vector3(0.0f, 10.0f, 0.0f))
			.create()
		);

		gameObject->addComponent(
			tktk::ColliderWireFrameDrawer3DMaker::makeStart()
			.drawPriority(100)
			.wireFrameColor(Color::white)
			.create()
		);

		// .renderTargetId(RenderTargetId::RENDER_TARGET_BEFOR_BLOOM)
	
		gameObject->addComponent(tktk::CurStateTypeListMaker::makeStart().create());
		MeshTestMoveState::create(gameObject);
		MeshTestRotateState::create(gameObject);
		MeshTestScaleState::create(gameObject);

		gameObject->addComponent(new MeshTestScript());

		gameObject->addChild(MeshTestChild::create(Vector3(0.0f, 0.0f, 0.0f)));
	}
};

#endif // !MESH_TEST_H_

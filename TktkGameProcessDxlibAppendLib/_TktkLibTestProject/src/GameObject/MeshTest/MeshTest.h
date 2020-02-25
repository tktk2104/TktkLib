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

		tktk::Transform3DMaker::makeStart(gameObject)
			//.position(Vector3(0.0f, 0.0f, 0.0f))
			.create();

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

		tktk::MeshDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.meshID(1)
			.createShadow(true)
			.shadowCreatorPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW)
			.meshLocalScale(Vector3(15.0f))
			.meshLocalRotation(Quaternion::identity)
			.create();

		tktk::MeshAnimatorMaker::makeStart(gameObject)
			.isLoop(true)
			.motionID(4)
			.motionIntervalSec(1.0f / 30.0f)
			.create();

		tktk::BoxColliderMaker::makeStart(gameObject)
			.collisionGroupType(CollisionGroup::COLLISION_GROUP_PLAYER)
			.boxSize(Vector3(15.0f, 22.0f, 15.0f))
			.localPosition(Vector3(0.0f, 10.0f, 0.0f))
			.create();

		tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
			.drawPriority(100)
			.wireFrameColor(Color::white)
			.create();

		// .renderTargetId(RenderTargetId::RENDER_TARGET_BEFOR_BLOOM)
	
		tktk::CurStateTypeListMaker::makeStart(gameObject).create();
		MeshTestMoveState::create(gameObject);
		MeshTestRotateState::create(gameObject);
		MeshTestScaleState::create(gameObject);

		gameObject->addComponent(new MeshTestScript());

		gameObject->addChild(MeshTestChild::create(Vector3(0.0f, 0.0f, 0.0f)));
	}
};

#endif // !MESH_TEST_H_

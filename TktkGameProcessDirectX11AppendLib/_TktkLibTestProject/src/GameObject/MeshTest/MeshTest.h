#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawerMaker.h>
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimatorMaker.h>
#include "MeshTestScript.h"


struct MeshTest
{
	static void create(const Vector3& position)
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(position)
			.create();

		tktk::MeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.cameraId(CAMERA_BASIC)
			.meshId(MESH_ROBOT_KYLE)
			.skeltonId(SKELETON_YBot)
			.materialIdArray(MATERIAL_ROBOT_KYLE)
			//.blendRate(Color(0.5f, 0.5f, 0.5f, 0.5f))
			.create();

		/*tktk::MeshAnimatorMaker::makeStart(gameObject)
			.animationId(ANIMATION_YBot_kicking_1)
			.create();*/

		gameObject->createComponent<MeshTestScript>();
	}
};
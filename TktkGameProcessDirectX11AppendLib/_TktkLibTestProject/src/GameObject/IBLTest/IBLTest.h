#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawerMaker.h>

struct IBLTest
{
	static void create(const Vector3& position)
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(position)
			.scaleRate(Vector3(0.5f))
			.create();

		tktk::MeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.cameraId(CAMERA_BASIC)
			.meshId(MESH_PISTOL)
			.skeltonId(-10)
			.materialIdArray(std::vector<int>({ MATERIAL_IBL_PISTOL }))
			.create();
	}
};
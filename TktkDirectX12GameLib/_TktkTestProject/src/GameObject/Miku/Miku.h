#ifndef MIKU_H_
#define MIKU_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/Transform3D/Transform3DMaker.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawerMaker.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/MeshAnimator/MeshAnimatorMaker.h>

#include "MikuScript.h"

struct Miku
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		tktk::BasicMeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.meshId(0U)
			.skeletonId(0U)
			.useRtvDescriptorHeapId(0U)
			.create();

		tktk::BasicMeshShadowMapWriterMaker::makeStart(gameObject)
			.drawPriority(-10.0f)
			.meshId(0U)
			.skeletonId(0U)
			.create();

		tktk::MeshAnimatorMaker::makeStart(gameObject)
			.initMotionId(1U)
			.create();

		gameObject->createComponent<MikuScript>();

		return gameObject;
	}
};
#endif // !MIKU_H_

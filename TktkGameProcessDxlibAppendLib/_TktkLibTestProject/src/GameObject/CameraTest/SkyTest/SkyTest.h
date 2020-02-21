#pragma once

#include "CommonIncludePaths.h"

class SkyTest
{
public:

	static GameObjectPtr create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.traceType(tktk::TraceParentType::TRACE_PARENT_POS_AND_SCALE)
			.create()
		);

		gameObject->addComponent(
			tktk::MeshDrawerMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_SKY)
			.meshID(MeshId::MESH_SKY)
			.writeZBuffer(false)
			.useLight(false)
			.create()
		);
		return gameObject;
	}
};
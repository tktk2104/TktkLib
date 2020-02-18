#pragma once

#include "CommonIncludePaths.h"

class SkyTest
{
public:

	static tktk::GameObjectPtr create()
	{
		tktk::GameObjectPtr gameObject = tktk::GameObject::create();

		gameObject.lock()->addComponent(
			tktk::Transform3DMaker::makeStart()
			.traceType(tktk::TraceParentType::TRACE_PARENT_POS_AND_SCALE)
			.create()
		);

		gameObject.lock()->addComponent(
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
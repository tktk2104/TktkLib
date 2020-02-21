#pragma once

#include "CommonIncludePaths.h"

struct RenderTargetTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::RenderTargetDrawerMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT + 10.0f)
			.drawRenderTargetId(RenderTargetId::RENDER_TARGET_BLOOM_COMBINE)
			.create()
		);
	}
};

#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Line2D/Line2DDrawerMaker.h>

struct Line2DTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			.position(Vector2(200.0f, 200.0f))
			//.scaleRate(Vector2(20.0f))
			.rotationDeg(90.0f)
			.create();

		tktk::Line2DDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.lineVertexArray({ Vector2(100.0f, 100.0f), Vector2(200.0f, 200.0f) })
			.lineColor(Color::red)
			.create();
	}
};
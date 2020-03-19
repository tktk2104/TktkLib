#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Text/TextDrawerMaker.h>

struct TextTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);
		
		tktk::Transform2DMaker::makeStart(gameObject)
			.position(Vector2(400.0f, 400.0f))
			.create();

		tktk::TextDrawerMaker::makeStart(gameObject)
			.drawPriority(10.0f)
			.initText("ABCDEFGHIJKLMNOPQRSTUVWXYZ:123456789.0f")
			.create();
	}
};
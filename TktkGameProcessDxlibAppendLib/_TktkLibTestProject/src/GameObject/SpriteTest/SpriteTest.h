#ifndef SPRITE_TEST_H_
#define SPRITE_TEST_H_

#include "CommonIncludePaths.h"

#include "SpriteTestScript.h"
#include "StopState/StopState.h"
#include "WalkState/WalkState.h"
#include "RunState/RunState.h"

struct SpriteTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			.position(tktk::Screen::getGameScreenSize() / 2)
			.scaleRate(Vector2(10))
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject).drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT).create();

		tktk::SpriteAnimatorMaker::makeStart(gameObject)
			.textureId(TEXTURE_ANIM_SAMPLE)
			.splitTextureIndexList<0, 1, 2, 3>()
			.animationIntervalSec(0.1f)
			.animSpeedRate(1.0f)
			.loop(true)
			.create();

		tktk::CurStateTypeListMaker::makeStart(gameObject).create();

		StopState::create(gameObject);
		WalkState::create(gameObject);
		RunState::create(gameObject);

		gameObject->addComponent(new SpriteTestScript());
	}
};
#endif // !SPRITE_TEST_H_
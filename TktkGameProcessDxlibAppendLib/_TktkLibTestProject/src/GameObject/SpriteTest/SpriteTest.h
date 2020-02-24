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

		gameObject->addComponent(
			tktk::Transform2DMaker::makeStart()
			.position(tktk::Screen::getGameScreenSize() / 2)
			.scaleRate(Vector2(10))
			.create()
		);

		gameObject->addComponent(
			tktk::SpriteDrawerMaker::makeStart().drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT).create()
		);

		gameObject->addComponent(
			tktk::SpriteAnimatorMaker::makeStart()
			.textureId(TEXTURE_ANIM_SAMPLE)
			.splitTextureIndexList<0,1,2,3>()
			.animationIntervalSec(0.1f)
			.animSpeedRate(1.0f)
			.loop(true)
			.create()
		);

		gameObject->addComponent(tktk::CurStateTypeListMaker::makeStart().create());

		StopState::create(gameObject);
		WalkState::create(gameObject);
		RunState::create(gameObject);

		gameObject->addComponent(new SpriteTestScript());
	}
};
#endif // !SPRITE_TEST_H_
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
		unsigned int i	= 1 << 1;	//0010
		unsigned int j	= 1 << 3;	//1000

		unsigned int ij	= i | j;	//1010
		
		unsigned int k	= 0b0101;	//0101
		
		unsigned int l	= ~i;		//1101
		
		unsigned int m	= (ij & ~i);//1000



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
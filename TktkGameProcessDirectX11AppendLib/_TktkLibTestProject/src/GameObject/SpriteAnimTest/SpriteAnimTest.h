#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingDrawerMaker.h>
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingAnimatorMaker.h>

struct SpriteAnimTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			.position(Vector2(100.0f, 100.0f))
			//.scaleRate(Vector2(20.0f))
			.create();

		tktk::SpriteClippingDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.textureId(TEXTURE_2D_SPRITE_ANIM_TEST)
			.textureClippingLeftTopPos(Vector2(64.0f * 1, 0.0f))
			.textureClippingSize(Vector2(64.0f))
			.create();

		tktk::SpriteClippingAnimatorMaker::makeStart(gameObject)
			.animationIntervalSec(1.0f)
			.animFrameTextureLeftTopPosArray({
				{ 0.0f, 0.0f },
				{ 64.0f, 0.0f },
				{ 64.0f * 2, 0.0f },
				{ 64.0f * 3, 0.0f }
				})
			.create();
	}
};
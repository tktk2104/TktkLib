#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingDrawerMaker.h>
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingAnimatorMaker.h>
#include <TktkAppendDirectX11Component/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h>

struct SpriteAnimTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			.position(Vector2(100.0f, 100.0f))
			.scaleRate(Vector2(10.0f))
			.rotationDeg(-45.0f)
			.create();

		tktk::SpriteClippingDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.textureId(TEXTURE_2D_SPRITE_ANIM_TEST)
			.textureClippingLeftTopPos(Vector2(64.0f * 0, 0.0f))
			.textureClippingSize(Vector2(64.0f))
			.create();

		tktk::CircleColliderMaker::makeStart(gameObject)
			.collisionGroupType(1)
			.localPosition(Vector2(30.0, 30.0f))
			.radius(32.0f)
			.create();

		/*tktk::RectColliderMaker::makeStart(gameObject)
			.collisionGroupType(1)
			.rectSize(Vector2(64.0f, 64.0f))
			.create();*/

		tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
			.drawPriority(10.0f)
			.lineColor(Color::red)
			.create();

		tktk::SpriteClippingAnimatorMaker::makeStart(gameObject)
			.animationIntervalSec(1.0f)
			.animFrameTextureLeftTopPosArray({
				{ 0.0f, 0.0f },
				{ 64.0f, 0.0f },
				{ 64.0f * 2, 0.0f },
				{ 64.0f * 3, 0.0f },
				{ 64.0f * 2, 0.0f },
				{ 64.0f * 1, 0.0f },
				})
			.create();
	}
};
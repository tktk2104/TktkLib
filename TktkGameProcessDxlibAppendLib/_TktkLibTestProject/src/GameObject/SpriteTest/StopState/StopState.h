#pragma once

#include "CommonIncludePaths.h"
#include "../SpriteTestState.h"

struct StopState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, SpriteTestState::STOP_STATE);

		stateMachine->addComponent(
			tktk::RectColliderMaker::makeStart()
			.rectSize(Vector2(128.0f, 128.0f))
			.collisionGroupType(1)
			.create()
		);

		stateMachine->addComponent(
			tktk::ColliderWireFrameDrawer2DMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT)
			.wireFrameColor(Color::red)
			.create()
		);

		return stateMachine;
	}
};
#pragma once

#include "CommonIncludePaths.h"
#include "../SpriteTestState.h"
#include "WalkStateScript.h"

struct WalkState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, SpriteTestState::WALK_STATE);

		stateMachine->addComponent(new WalkStateScript());

		return stateMachine;
	}
};
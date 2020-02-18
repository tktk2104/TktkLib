#pragma once

#include "CommonIncludePaths.h"
#include "../SpriteTestState.h"
#include "WalkStateScript.h"

struct WalkState
{
	static tktk::StateMachinePtr create(tktk::GameObjectPtr user)
	{
		tktk::StateMachinePtr stateMachine = tktk::StateMachine::create(user, SpriteTestState::WALK_STATE);

		stateMachine.lock()->addComponent(std::make_shared<WalkStateScript>());

		return stateMachine;
	}
};
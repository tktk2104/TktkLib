#pragma once

#include "CommonIncludePaths.h"
#include "../SpriteTestState.h"
#include "RunStateScript.h"

struct RunState
{
	static tktk::StateMachinePtr create(tktk::GameObjectPtr user)
	{
		tktk::StateMachinePtr stateMachine = tktk::StateMachine::create(user, SpriteTestState::RUN_STATE);

		stateMachine.lock()->addComponent(std::make_shared<RunStateScript>());

		return stateMachine;
	}
};
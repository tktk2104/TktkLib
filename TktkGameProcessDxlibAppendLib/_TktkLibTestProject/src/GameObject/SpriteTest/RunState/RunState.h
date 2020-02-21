#pragma once

#include "CommonIncludePaths.h"
#include "../SpriteTestState.h"
#include "RunStateScript.h"

struct RunState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, SpriteTestState::RUN_STATE);

		stateMachine->addComponent(new RunStateScript());

		return stateMachine;
	}
};
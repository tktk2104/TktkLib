#pragma once

#include "CommonIncludePaths.h"
#include "SelfScaler.h"
#include "../MeshTestState.h"

struct MeshTestScaleState
{
	static tktk::StateMachinePtr create(tktk::GameObjectPtr user)
	{
		tktk::StateMachinePtr stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_SCALE_STATE);

		stateMachine.lock()->addComponent(std::make_shared<SelfScaler>());

		return stateMachine;
	}
};
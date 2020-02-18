#pragma once

#include "CommonIncludePaths.h"
#include "SelfMover.h"
#include "../MeshTestState.h"

struct MeshTestMoveState
{
	static tktk::StateMachinePtr create(tktk::GameObjectPtr user)
	{
		tktk::StateMachinePtr stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_MOVE_STATE);

		stateMachine.lock()->addComponent(std::make_shared<SelfMover>());

		return stateMachine;
	}
};
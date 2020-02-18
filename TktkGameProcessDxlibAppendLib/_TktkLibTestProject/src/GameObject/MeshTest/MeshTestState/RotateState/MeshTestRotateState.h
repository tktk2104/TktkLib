#pragma once

#include "CommonIncludePaths.h"
#include "SelfRotater.h"
#include "../MeshTestState.h"

struct MeshTestRotateState
{
	static tktk::StateMachinePtr create(tktk::GameObjectPtr user)
	{
		tktk::StateMachinePtr stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_ROTATE_STATE);

		stateMachine.lock()->addComponent(std::make_shared<SelfRotater>());

		return stateMachine;
	}
};
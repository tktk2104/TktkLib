#pragma once

#include "CommonIncludePaths.h"
#include "SelfMover.h"
#include "../MeshTestState.h"

struct MeshTestMoveState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_MOVE_STATE);

		stateMachine->addComponent(new SelfMover());

		return stateMachine;
	}
};
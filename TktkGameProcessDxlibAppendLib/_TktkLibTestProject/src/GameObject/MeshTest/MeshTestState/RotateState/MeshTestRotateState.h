#pragma once

#include "CommonIncludePaths.h"
#include "SelfRotater.h"
#include "../MeshTestState.h"

struct MeshTestRotateState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_ROTATE_STATE);

		stateMachine->addComponent(new SelfRotater());

		return stateMachine;
	}
};
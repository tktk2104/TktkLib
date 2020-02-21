#pragma once

#include "CommonIncludePaths.h"
#include "SelfScaler.h"
#include "../MeshTestState.h"

struct MeshTestScaleState
{
	static tktk::CfpPtr<tktk::StateMachine> create(GameObjectPtr user)
	{
		auto stateMachine = tktk::StateMachine::create(user, MeshTestState::MESH_TEST_SCALE_STATE);

		stateMachine->addComponent(new SelfScaler());

		return stateMachine;
	}
};
#pragma once

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "../Enums/CollisionGroup.h"

struct CollisionGroupSetter
{
	static void set()
	{
		tktk::ComponentFrameworkProcessor::addCollisionGroupPair(
			COLLISION_GROUP_A, COLLISION_GROUP_B
		);
	}
};
#pragma once

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

#include "../TestObject/GameObject/TestGameObjectScript_1.h"
#include "../TestObject/GameObject/TestGameObjectScript_2.h"

// �N���X����Update�֐��̍X�V�D��x�����߂�֐�
struct UpdatePrioritySetter
{
	static void set()
	{
		//tktk::ComponentFrameworkProcessor::addUpdatePriority<>(0.0f);

		//tktk::ComponentFrameworkProcessor::addUpdatePriority<TestGameObjectScript_1>(100.0f);
		//tktk::ComponentFrameworkProcessor::addUpdatePriority<TestGameObjectScript_2>(-100.0f);
	}
};
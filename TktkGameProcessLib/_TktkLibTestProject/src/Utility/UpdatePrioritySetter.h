#pragma once

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

#include "../TestObject/GameObject/TestGameObjectScript_1.h"
#include "../TestObject/GameObject/TestGameObjectScript_2.h"

// クラス毎にUpdate関数の更新優先度を決める関数
struct UpdatePrioritySetter
{
	static void set()
	{
		//tktk::ComponentFrameworkProcessor::addUpdatePriority<>(0.0f);

		//tktk::ComponentFrameworkProcessor::addUpdatePriority<TestGameObjectScript_1>(100.0f);
		//tktk::ComponentFrameworkProcessor::addUpdatePriority<TestGameObjectScript_2>(-100.0f);
	}
};
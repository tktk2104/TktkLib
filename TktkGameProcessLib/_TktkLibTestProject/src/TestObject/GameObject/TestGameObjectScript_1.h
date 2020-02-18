#pragma once

#include <iostream>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TestGameObjectScript_2.h"

class TestGameObjectScript_1
	: public tktk::ComponentBase
{
public:

	void start()
	{
		/*getGameObject().lock()->addComponent(
			std::make_shared<TestGameObjectScript_2>()
		);*/
	};

	void update()
	{
		//getGameObject().lock()->destroy();
		std::cout << "TestGameObjectScript_1" << std::endl;
	};
};
#pragma once

#include <TktkComponentFramework/Scene/SceneBase.h>

class MainScene
	: public tktk::SceneBase
{
public:

	void sceneStart() override;

	void sceneEnd() override;
};
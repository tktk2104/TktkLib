#pragma once

#include <TktkComponentFramework/Scene/SceneBase.h>

class LoadScene
	: public tktk::SceneBase
{
public:

	void sceneStart() override;

	void sceneEnd() override;
};
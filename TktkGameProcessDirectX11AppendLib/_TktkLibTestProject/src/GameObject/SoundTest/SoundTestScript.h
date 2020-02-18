#pragma once

#include "CommonIncludePaths.h"

class SoundTestScript
	: tktk::ComponentBase
{
public:

	SoundTestScript();

public:

	void start();
	void update();

private:

	float m_masterVolume{ 1.0f };
};
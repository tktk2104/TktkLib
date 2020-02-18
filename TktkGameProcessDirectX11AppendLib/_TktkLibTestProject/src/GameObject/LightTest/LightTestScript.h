#pragma once

#include "CommonIncludePaths.h"

class LightTestScript
	: public tktk::ComponentBase
{
public:

	LightTestScript();

public:

	void update();

private:

	float m_curRotationDeg{ 0.0f };
};
#pragma once

#include "CommonIncludePaths.h"

class StopStateScript
	: public tktk::ComponentBase
{
public:

	StopStateScript() = default;

public:

	void start();
	void update();
};
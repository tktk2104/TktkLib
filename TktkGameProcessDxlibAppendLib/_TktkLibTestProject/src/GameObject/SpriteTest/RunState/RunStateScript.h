#pragma once

#include "CommonIncludePaths.h"

class RunStateScript
	: public tktk::ComponentBase
{
public:

	RunStateScript() = default;

public:

	void start();
	void update();
};
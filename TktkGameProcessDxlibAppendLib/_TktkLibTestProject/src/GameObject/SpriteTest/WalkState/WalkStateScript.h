#pragma once

#include "CommonIncludePaths.h"

class WalkStateScript
	: public tktk::ComponentBase
{
public:

	WalkStateScript() = default;

public:

	void start();
	void update();
};
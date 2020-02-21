#pragma once

#include "CommonIncludePaths.h"

class SelfMover
	: public tktk::ComponentBase
{
public:

	SelfMover() = default;

public:

	void start();
	void update();

private:

	tktk::CfpPtr<tktk::Transform3D> m_transform;
};
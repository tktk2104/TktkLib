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

	std::weak_ptr<tktk::Transform3D> m_transform;
};
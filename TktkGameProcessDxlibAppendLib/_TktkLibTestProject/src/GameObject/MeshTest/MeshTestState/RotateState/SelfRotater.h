#pragma once

#include "CommonIncludePaths.h"

class SelfRotater
	: public tktk::ComponentBase
{
public:

	SelfRotater() = default;

public:

	void start();
	void update();

private:

	std::weak_ptr<tktk::Transform3D> m_transform;
};
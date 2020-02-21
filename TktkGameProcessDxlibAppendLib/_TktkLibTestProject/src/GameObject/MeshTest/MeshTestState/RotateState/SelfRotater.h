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

	tktk::CfpPtr<tktk::Transform3D> m_transform;
};
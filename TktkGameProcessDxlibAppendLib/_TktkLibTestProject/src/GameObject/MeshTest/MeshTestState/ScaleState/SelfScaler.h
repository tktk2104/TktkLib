#pragma once

#include "CommonIncludePaths.h"

class SelfScaler
	: public tktk::ComponentBase
{
public:

	SelfScaler() = default;

public:

	void start();
	void update();

private:

	std::weak_ptr<tktk::Transform3D> m_transform;
};
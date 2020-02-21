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

	tktk::CfpPtr<tktk::Transform3D> m_transform;
};
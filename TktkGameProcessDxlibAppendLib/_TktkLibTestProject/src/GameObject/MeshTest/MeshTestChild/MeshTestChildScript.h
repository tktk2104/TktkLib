#pragma once

#include "CommonIncludePaths.h"

class MeshTestChildScript
	: public tktk::ComponentBase
{
public:

	MeshTestChildScript() = default;

public:

	void start();
	void update();
	void afterChangeParent(GameObjectPtr beforParent);

private:

	tktk::CfpPtr<tktk::Transform3D> m_transform;

	GameObjectPtr m_parent;

	int m_curBone{ 2 };
};
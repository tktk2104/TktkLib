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
	void afterChangeParent(tktk::GameObjectPtr beforParent);

private:

	std::weak_ptr<tktk::Transform3D> m_transform;

	tktk::GameObjectPtr m_parent;

	int m_curBone{ 2 };
};
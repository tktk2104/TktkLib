#ifndef MESH_TEST_SCRIPT_H_
#define MESH_TEST_SCRIPT_H_

#include "CommonIncludePaths.h"

class MeshTestScript
	: public tktk::ComponentBase
{
public:

	MeshTestScript() = default;

public:

	void start();
	void update();
	void onCollisionEnter(tktk::GameObjectPtr other);
	void onCollisionStay(tktk::GameObjectPtr other);
	void onCollisionExit(tktk::GameObjectPtr other);

private:

	std::weak_ptr<tktk::CurStateTypeList> m_curStateTypeList;

	tktk::GameObjectPtr m_child;
};
#endif // !MESH_TEST_SCRIPT_H_
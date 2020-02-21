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
	void onCollisionEnter(GameObjectPtr other);
	void onCollisionStay(GameObjectPtr other);
	void onCollisionExit(GameObjectPtr other);

private:

	tktk::CfpPtr<tktk::CurStateTypeList> m_curStateTypeList;

	GameObjectPtr m_child;
};
#endif // !MESH_TEST_SCRIPT_H_
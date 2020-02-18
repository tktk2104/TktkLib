#include "LightTestScript.h"

#include <TktkMath/Matrix4.h>

LightTestScript::LightTestScript()
{
}

void LightTestScript::update()
{
	m_curRotationDeg += 0.1f;

	Matrix4 localMat = Matrix4::createTranslation(Vector3(0.0f, 3.0f, -5.0f)) * Matrix4::createRotationY(m_curRotationDeg);

	getComponent<tktk::Transform3D>()->setWorldPosition(localMat.calculateTranslation());
}

#ifndef CAMERA_TEST_SCRIPT_H_
#define CAMERA_TEST_SCRIPT_H_

#include <memory>
#include "CommonIncludePaths.h"

class CameraTestScript
	: public tktk::ComponentBase
{
public:

	CameraTestScript() = default;

public:

	void start();
	void update();

private:

	std::weak_ptr<tktk::Transform3D> m_transform;

	// TODO : ���̕ϐ����g��Ȃ�����
	Vector3 m_curCameraRotation{ 0.0f, 180.0f, 0.0f };
};
#endif // !CAMERA_TEST_SCRIPT_H_
#ifndef CAMERA_TEST_SCRIPT_H_
#define CAMERA_TEST_SCRIPT_H_

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

	tktk::CfpPtr<tktk::Transform3D> m_transform;

	// TODO : ‚±‚Ì•Ï”‚ğg‚í‚È‚¢À‘•
	Vector3 m_curCameraRotation{ 0.0f, 180.0f, 0.0f };
};
#endif // !CAMERA_TEST_SCRIPT_H_
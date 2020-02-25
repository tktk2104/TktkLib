#include "TktkAppendDxlib3DComponent/Graphics/Camera/BasicCameraMaker.h"

namespace tktk
{
	BasicCameraMaker BasicCameraMaker::m_self;

	BasicCameraMaker & BasicCameraMaker::makeStart(GameObjectPtr user)
	{
		m_self = BasicCameraMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<BasicCamera> BasicCameraMaker::create()
	{
		return m_user->createComponent<BasicCamera>(
			m_drawPriority,
			m_initCameraFov,
			m_initCameraAspectRate,
			m_initCameraDrawingRangeNear,
			m_initCameraDrawingRangeFar
			);
	}

	BasicCameraMaker & BasicCameraMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	BasicCameraMaker & BasicCameraMaker::initCameraFov(float value)
	{
		m_initCameraFov = value;
		return *this;
	}

	BasicCameraMaker & BasicCameraMaker::initCameraAspectRate(float value)
	{
		m_initCameraAspectRate = value;
		return *this;
	}

	BasicCameraMaker & BasicCameraMaker::initCameraDrawingRangeNear(float value)
	{
		m_initCameraDrawingRangeNear = value;
		return *this;
	}

	BasicCameraMaker & BasicCameraMaker::initCameraDrawingRangeFar(float value)
	{
		m_initCameraDrawingRangeFar = value;
		return *this;
	}
}
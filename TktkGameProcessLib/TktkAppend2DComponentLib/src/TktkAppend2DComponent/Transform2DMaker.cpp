#include "TktkAppend2DComponent/Transform2D.h"
#include "TktkAppend2DComponent/Transform2DMaker.h"

namespace tktk
{
	Transform2DMaker Transform2DMaker::m_self;

	Transform2DMaker & Transform2DMaker::makeStart()
	{
		m_self = Transform2DMaker();
		return m_self;
	}

	Transform2D* Transform2DMaker::create()
	{
		return new Transform2D(
			m_initPosition,
			m_initScaleRate,
			m_initRotationDeg,
			m_traceType
		);
	}

	Transform2DMaker & Transform2DMaker::position(const Vector2 & value)
	{
		m_initPosition = value;
		return *this;
	}

	Transform2DMaker & Transform2DMaker::scaleRate(const Vector2 & value)
	{
		m_initScaleRate = value;
		return *this;
	}

	Transform2DMaker & Transform2DMaker::rotationDeg(float value)
	{
		m_initRotationDeg = value;
		return *this;
	}

	Transform2DMaker & Transform2DMaker::traceType(TraceParentType value)
	{
		m_traceType = value;
		return *this;
	}
}
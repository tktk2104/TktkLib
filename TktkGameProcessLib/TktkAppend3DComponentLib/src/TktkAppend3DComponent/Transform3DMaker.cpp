#include "TktkAppend3DComponent/Transform3DMaker.h"

namespace tktk
{
	Transform3DMaker Transform3DMaker::m_self;

	Transform3DMaker & Transform3DMaker::makeStart()
	{
		m_self = Transform3DMaker();
		return m_self;
	}

	Transform3D* Transform3DMaker::create()
	{
		return new Transform3D(
			m_initPosition,
			m_initScaleRate,
			m_initRotation,
			m_traceType
		);
	}

	Transform3DMaker & Transform3DMaker::position(const Vector3 & value)
	{
		m_initPosition = value;
		return *this;
	}

	Transform3DMaker & Transform3DMaker::scaleRate(const Vector3 & value)
	{
		m_initScaleRate = value;
		return *this;
	}

	Transform3DMaker & Transform3DMaker::rotation(const Quaternion & value)
	{
		m_initRotation = value;
		return *this;
	}

	Transform3DMaker & Transform3DMaker::rotationDeg(const Vector3 & value)
	{
		m_initRotation = Quaternion::createFromEulerAngle(value);
		return *this;
	}

	Transform3DMaker & Transform3DMaker::traceType(TraceParentType value)
	{
		m_traceType = value;
		return *this;
	}
}
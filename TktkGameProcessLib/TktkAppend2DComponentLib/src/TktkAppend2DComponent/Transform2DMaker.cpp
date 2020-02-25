#include "TktkAppend2DComponent/Transform2D.h"
#include "TktkAppend2DComponent/Transform2DMaker.h"

namespace tktk
{
	Transform2DMaker Transform2DMaker::m_self;

	Transform2DMaker & Transform2DMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<Transform2D> Transform2DMaker::create()
	{
		return m_user->createComponent<Transform2D>(
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

	void Transform2DMaker::reset()
	{
		m_self.m_initPosition = Vector2::zero;
		m_self.m_initScaleRate = Vector2::one;
		m_self.m_initRotationDeg = 0.0f;
		m_self.m_traceType = TraceParentType::TRACE_PARENT_ALL;
	}
}
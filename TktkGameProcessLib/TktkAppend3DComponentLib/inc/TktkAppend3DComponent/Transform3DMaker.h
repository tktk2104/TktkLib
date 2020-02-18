#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include "Transform3D.h"

namespace tktk
{
	class Transform3DMaker
	{
	public:

		static Transform3DMaker& makeStart();

	public:

		Transform3D* create();

		Transform3DMaker& position(const Vector3& value);

		Transform3DMaker& scaleRate(const Vector3& value);

		Transform3DMaker& rotation(const Quaternion& value);

		Transform3DMaker& rotationDeg(const Vector3& value);

		Transform3DMaker& traceType(TraceParentType value);

	private:

		static Transform3DMaker m_self;

	private:

		Vector3 m_initPosition{ Vector3::zero };
		Vector3 m_initScaleRate{ Vector3::one };
		Quaternion m_initRotation{ Quaternion::identity };
		TraceParentType m_traceType{ TraceParentType::TRACE_PARENT_ALL };
	};
}
#endif // !TRANSFORM_3D_MAKER_H_
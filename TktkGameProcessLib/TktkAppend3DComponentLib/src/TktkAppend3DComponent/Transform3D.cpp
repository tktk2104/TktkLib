#include "TktkAppend3DComponent/Transform3D.h"

#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkMath/Quaternion.h>

namespace tktk
{
	Transform3D::Transform3D(
		const Vector3 & initPosition,
		const Vector3 & initScaleRate,
		const Quaternion & initRotation,
		TraceParentType traceType
	)
		: m_localPosition(initPosition)
		, m_localScaleRate(initScaleRate)
		, m_localRotation(initRotation)
		, m_traceType(traceType)
	{
	}

	void Transform3D::start()
	{
		auto parentTransform		= findParentTransform3D();
		Matrix4 parentTraceUseMat	= calculateTraceUseMat(parentTransform, m_traceType);
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
	}

	void Transform3D::afterChangeParent(CfpPtr<GameObject> beforParent)
	{
		auto curParent = getGameObject()->getParent();
		if (beforParent.isNull() && !curParent.isNull()) enableParentTransform(curParent);
		if (!beforParent.isNull() && curParent.isNull()) disableParentTransform(beforParent);
	}

	const Vector3 & Transform3D::getWorldPosition() const
	{ return m_worldPosition; }

	const Vector3 & Transform3D::getWorldScaleRate() const
	{ return m_worldScaleRate; }

	const Quaternion & Transform3D::getWorldRotation() const
	{ return m_worldRotation; }

	Vector3 Transform3D::calculateWorldEulerAngles() const
	{ return getWorldRotation().calculateEulerAngle(); }

	const Vector3 & Transform3D::getLocalPosition() const
	{ return m_localPosition; }

	const Vector3 & Transform3D::getLocalScaleRate() const
	{ return m_localScaleRate; }

	const Quaternion & Transform3D::getLocalRotation() const
	{ return m_localRotation; }

	Vector3 Transform3D::calculateLocalEulerAngles() const
	{ return getLocalRotation().calculateEulerAngle(); }

	Matrix4 Transform3D::calculateWorldMatrix() const
	{
		return Matrix4::createTRS(m_worldPosition, m_worldRotation, m_worldScaleRate);
	}

	Matrix4 Transform3D::calculateLocalMatrix() const
	{
		return Matrix4::createTRS(m_localPosition, m_localRotation, m_localScaleRate);
	}

	void Transform3D::addWorldPosition(const Vector3 & position)
	{
		setWorldPosition(m_worldPosition + position);
	}

	void Transform3D::addWorldRotation(const Quaternion & rotation)
	{
		setWorldRotation(m_localRotation + rotation);
	}

	void Transform3D::addWorldEulerAngles(const Vector3 & eulerAngles)
	{
		setWorldRotation(m_localRotation * Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::addLocalPosition(const Vector3 & position)
	{
		setLocalPosition(m_localPosition + position);
	}

	void Transform3D::addLocalScaleRate(const Vector3 & scaleRate)
	{
		setLocalScaleRate(m_localScaleRate + scaleRate);
	}

	void Transform3D::addLocalRotation(const Quaternion & rotation)
	{
		setLocalRotation(m_localRotation * rotation);
	}

	void Transform3D::addLocalEulerAngles(const Vector3 & eulerAngles)
	{
		setLocalRotation(m_localRotation * Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setWorldPosition(const Vector3 & position)
	{
		m_worldPosition = position;

		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setWorldRotation(const Quaternion & rotation)
	{
		m_worldRotation = rotation;

		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setWorldEulerAngles(const Vector3 & eulerAngles)
	{
		setWorldRotation(Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setWorldAxisAngle(const Vector3 & axis, float degree)
	{
		setWorldRotation(Quaternion::createFromAxisAngle(axis, degree));
	}

	void Transform3D::setLocalPosition(const Vector3 & position)
	{
		m_localPosition = position;

		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalScaleRate(const Vector3 & scaleRate)
	{
		m_localScaleRate = scaleRate;

		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalRotation(const Quaternion & rotation)
	{
		m_localRotation = rotation;

		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalEulerAngles(const Vector3 & eulerAngles)
	{
		setLocalRotation(Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setLocalAxisAngle(const Vector3 & axis, float degree)
	{
		setLocalRotation(Quaternion::createFromAxisAngle(axis, degree));
	}

	Vector3 Transform3D::calculateWorldForwardLH() const
	{ return calculateWorldMatrix().calculateForwardLH(); }

	Vector3 Transform3D::calculateWorldForwardRH() const
	{ return calculateWorldMatrix().calculateForwardRH(); }

	Vector3 Transform3D::calculateWorldRight() const
	{ return calculateWorldMatrix().calculateRight(); }

	Vector3 Transform3D::calculateWorldUp() const
	{ return calculateWorldMatrix().calculateUp(); }

	Vector3 Transform3D::calculateLocalForwardLH() const
	{ return calculateLocalMatrix().calculateForwardLH(); }

	Vector3 Transform3D::calculateLocalForwardRH() const
	{ return calculateLocalMatrix().calculateForwardRH(); }

	Vector3 Transform3D::calculateLocalRight() const
	{ return calculateLocalMatrix().calculateRight(); }

	Vector3 Transform3D::calculateLocalUp() const
	{ return calculateLocalMatrix().calculateUp(); }

	void Transform3D::setWorldForwardLH(const Vector3 & forward)
	{
		setWorldRotation(Quaternion::createLookRotation(forward));
	}

	void Transform3D::setWorldForwardRH(const Vector3 & forward)
	{
		setWorldRotation(Quaternion::createLookRotation(forward));
	}

	void Transform3D::setWorldRight(const Vector3 & right)
	{
		setWorldRotation(Quaternion::createFromToRotation(Vector3::right, right));
	}

	void Transform3D::setWorldUp(const Vector3 & up)
	{
		setWorldRotation(Quaternion::createFromToRotation(Vector3::up, up));
	}

	void Transform3D::setLocalForwardLH(const Vector3 & forward)
	{
		setLocalRotation(Quaternion::createLookRotation(forward));
	}

	void Transform3D::setLocalForwardRH(const Vector3 & forward)
	{
		setLocalRotation(Quaternion::createLookRotation(forward));
	}

	void Transform3D::setLocalRight(const Vector3 & right)
	{
		setLocalRotation(Quaternion::createFromToRotation(Vector3::right, right));
	}

	void Transform3D::setLocalUp(const Vector3 & up)
	{
		setLocalRotation(Quaternion::createFromToRotation(Vector3::up, up));
	}

	void Transform3D::lookAt(CfpPtr<Transform3D> target, const Vector3 & worldUp)
	{
		if (target.isNull())
		{
			throw std::runtime_error("target Transform3D not found");
		}
		Vector3 targetPosition = target->getWorldPosition();

		lookAt(targetPosition, worldUp);
	}

	void Transform3D::lookAt(const Vector3 & target, const Vector3 & worldUp)
	{
		setWorldRotation(Quaternion::createLookRotation(target, worldUp));
	}

	void Transform3D::rotateAround(const Vector3 & worldPoint, const Vector3 & axis, float angle)
	{
		Vector3 relativeSelfWorldPos = m_worldPosition - worldPoint;

		setWorldPosition(Quaternion::createFromAxisAngle(axis, angle) * relativeSelfWorldPos + worldPoint);
	}

	/*Matrix4 Transform3D::calculateLocalToWorldMatrix() const
	{
		return Matrix4::createTranslation(-m_worldPosition);
	}

	Matrix4 Transform3D::calculateWorldToLocalMatrix() const
	{
		return calculateLocalToWorldMatrix().inverse();
	}*/

	Matrix4 Transform3D::calculateTraceUseMat(CfpPtr<Transform3D> target, TraceParentType traceType)
	{
		if (target.isNull()) return Matrix4::identity;

		Matrix4 traceUseMatrix = Matrix4::identity;

		if ((traceType & TRACE_PARENT_SCALE) != 0)
		{
			traceUseMatrix *= Matrix4::createScale(target->getWorldScaleRate());
		}

		if ((traceType & TRACE_PARENT_ROTATION) != 0)
		{
			traceUseMatrix *= Matrix4::createFromQuaternion(target->getWorldRotation());
		}

		if ((traceType & TRACE_PARENT_POS) != 0)
		{
			traceUseMatrix *= Matrix4::createTranslation(target->getWorldPosition());
		}
		return traceUseMatrix;
	}

	Vector3 Transform3D::calculateTraceUseScale(CfpPtr<Transform3D> target, TraceParentType traceType)
	{
		if (target.isNull()) return Vector3::one;

		Vector3 traceUseScale = Vector3::one;

		if ((traceType & TRACE_PARENT_SCALE) != 0)
		{
			traceUseScale = target->getWorldScaleRate();
		}
		return traceUseScale;
	}

	Vector3 Transform3D::calculateTraceUseInvScale(CfpPtr<Transform3D> target, TraceParentType traceType)
	{
		Vector3 traceUseInvScale = calculateTraceUseScale(target, traceType);

		return Vector3(
			1.0f / traceUseInvScale.x,
			1.0f / traceUseInvScale.y,
			1.0f / traceUseInvScale.z
		);
	}

	// 新しいローカル行列を指定して自身のローカルのトランスフォームを更新する
	void Transform3D::updateLocalTransform(const Matrix4 & newLocalMat, const Vector3 newLocalScale)
	{
		m_localPosition = newLocalMat.calculateTranslation();
		m_localRotation = newLocalMat.calculateRotation();
		m_localScaleRate = newLocalScale;
	}

	// 新しいワールド行列を指定して自身のワールドのトランスフォームを更新する
	void Transform3D::updateWorldTransform(const Matrix4 & newWorldMat, const Vector3 newWorldScale)
	{
		m_worldPosition = newWorldMat.calculateTranslation();
		m_worldRotation = newWorldMat.calculateRotation();
		m_worldScaleRate = newWorldScale;
	}

	/*Matrix4 Transform3D::calculateTraceUseInvMat()
	{
		Matrix4 traceUseInvMatrix = Matrix4::identity;

		if ((m_traceType & TRACE_PARENT_POS) != 0)
		{
			traceUseInvMatrix *= Matrix4::createTranslation(-getWorldPosition());
		}

		if ((m_traceType & TRACE_PARENT_ROTATION) != 0)
		{
			traceUseInvMatrix *= Matrix4::createFromQuaternion(Quaternion::calculateInvert(getWorldRotation()));
		}

		if ((m_traceType & TRACE_PARENT_SCALE) != 0)
		{
			traceUseInvMatrix *= Matrix4::createScale(Vector3(1.0f / getWorldScaleRate().x, 1.0f / getWorldScaleRate().y, 1.0f / getWorldScaleRate().z));
		}
		return traceUseInvMatrix;
	}*/

	// 親のTransform3Dを探す
	CfpPtr<Transform3D> Transform3D::findParentTransform3D() const
	{
		CfpPtr<GameObject> parent = getGameObject()->getParent();
		if (parent.isNull()) return CfpPtr<Transform3D>();
		return parent->getComponent<Transform3D>();
	}

	// 全ての子供のTransform3Dを更新する
	void Transform3D::updateAllChildTransform()
	{
		auto childList = getGameObject()->getChildren();

		std::for_each(
			std::begin(childList),
			std::end(childList),
			[this](const auto& node) { updateChildTransform(node); }
		);
	}

	// 指定した子供のTransform3Dを更新する
	void Transform3D::updateChildTransform(CfpPtr<GameObject> child)
	{
		auto childTransform = child->getComponent<Transform3D>();
		if (childTransform.isNull()) return;

		auto parentTransform = childTransform->findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, childTransform->m_traceType);
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, childTransform->m_traceType);
		childTransform->updateWorldTransform(
			childTransform->calculateLocalMatrix() * parentTraceUseMat, 
			Vector3::scale(childTransform->getLocalScaleRate(), parentTraceUseScale)
		);

		childTransform->updateAllChildTransform();
	}

	// 親のTransform3Dの追従を開始
	void Transform3D::enableParentTransform(CfpPtr<GameObject> curParent)
	{
		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, Vector3::scale(getLocalScaleRate(), parentTraceUseScale));

		findAndUpdateRootTransform(this);
	}

	// 親のTransform3Dの追従を終了
	void Transform3D::disableParentTransform(CfpPtr<GameObject> beforParent)
	{
		auto parentTransform = findParentTransform3D();
		Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseMat, Vector3::scale(getWorldScaleRate(), parentTraceUseScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, Vector3::scale(getLocalScaleRate(), parentTraceUseInvScale));

		findAndUpdateRootTransform(this);
	}

	// 大元のTransformから全ての子供を更新する（生ポインタ版）
	void Transform3D::findAndUpdateRootTransform(Transform3D* curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform3D();

		if (curParentTransform.isNull())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}

	// 大元のTransformから全ての子供を更新する（CfpPtr版）
	void Transform3D::findAndUpdateRootTransform(CfpPtr<Transform3D> curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform3D();

		if (curParentTransform.isNull())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}
}
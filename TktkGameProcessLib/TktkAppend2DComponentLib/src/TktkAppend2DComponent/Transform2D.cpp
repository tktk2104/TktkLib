#include "TktkAppend2DComponent/Transform2D.h"

#include <algorithm>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkMath/Quaternion.h>

namespace tktk
{
	Transform2D::Transform2D(
		const Vector2 & initPosition,
		const Vector2 & initScaleRate,
		float initRotationDeg,
		TraceParentType traceType
	)
		: m_localPosition(initPosition)
		, m_localScaleRate(initScaleRate)
		, m_localRotationDeg(initRotationDeg)
		, m_traceType(traceType)
	{
	}

	void Transform2D::start()
	{
		if (!getGameObject()->getParent().isNull()) m_isTransformParent = true;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
	}

	void Transform2D::update()
	{
		isTransformParentCheck(findParentTransform2D());
	}

	// ワールド座標を取得
	const Vector2 & Transform2D::getWorldPosition() const
	{ return m_worldPosition; }
	// ワールドスケールを取得
	const Vector2 & Transform2D::getWorldScaleRate() const
	{ return m_worldScaleRate; }
	// ワールド回転を取得
	float Transform2D::getWorldRotationDeg() const
	{ return m_worldRotationDeg; }

	// ローカル座標を取得
	const Vector2 & Transform2D::getLocalPosition()	const
	{ return m_localPosition; }
	// ローカルスケールを取得
	const Vector2 & Transform2D::getLocalScaleRate() const
	{ return m_localScaleRate; }
	// ローカル回転を取得
	float Transform2D::getLocalRotationDeg() const
	{ return m_localRotationDeg; }

	// ワールドの行列を計算
	Matrix3 Transform2D::calculateWorldMatrix() const
	{
		Matrix3 worldMatrix
			= Matrix3::createScale(m_worldScaleRate)
			* Matrix3::createRotation(m_worldRotationDeg)
			* Matrix3::createTranslation(m_worldPosition);

		return worldMatrix;
	}
	// ローカルの行列を計算
	Matrix3 Transform2D::calculateLocalMatrix() const
	{
		Matrix3 localMatrix
			= Matrix3::createScale(m_localScaleRate)
			* Matrix3::createRotation(m_localRotationDeg)
			* Matrix3::createTranslation(m_localPosition);

		return localMatrix;
	}

	// ワールド座標を指定分だけ増加
	void Transform2D::addWorldPosition(const Vector2 & position)
	{
		setWorldPosition(m_worldPosition + position);
	}
	// ワールドスケールを指定分だけ増加
	void Transform2D::addWorldScaleRate(const Vector2 & scaleRate)
	{
		setWorldScaleRate(m_worldScaleRate + scaleRate);
	}
	// ワールド回転を指定分だけ増加
	void Transform2D::addWorldRotationDeg(float rotationDeg)
	{
		setWorldRotationDeg(m_localRotationDeg + rotationDeg);
	}

	// ローカル座標を指定分だけ増加
	void Transform2D::addLocalPosition(const Vector2 & position)
	{
		setLocalPosition(m_localPosition + position);
	}
	// ローカルスケールを指定分だけ増加
	void Transform2D::addLocalScaleRate(const Vector2 & scaleRate)
	{
		setLocalScaleRate(m_localScaleRate + scaleRate);
	}
	// ローカル回転を指定分だけ増加
	void Transform2D::addLocalRotationDeg(float rotationDeg)
	{
		setLocalRotationDeg(m_localRotationDeg + rotationDeg);
	}

	// ワールド座標を設定
	void Transform2D::setWorldPosition(const Vector2 & position)
	{
		m_worldPosition = position;
		updateLocalTransform(calculateWorldMatrix() * Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}
	// ワールドスケールを設定
	void Transform2D::setWorldScaleRate(const Vector2 & scaleRate)
	{
		m_worldScaleRate = scaleRate;
		updateLocalTransform(calculateWorldMatrix() * Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}
	// ワールド回転を設定
	void Transform2D::setWorldRotationDeg(float rotationDeg)
	{
		m_worldRotationDeg = rotationDeg;
		updateLocalTransform(calculateWorldMatrix() * Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}

	// ローカル座標を設定
	void Transform2D::setLocalPosition(const Vector2 & position)
	{
		m_localPosition = position;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}
	// ローカルスケールを設定
	void Transform2D::setLocalScaleRate(const Vector2 & scaleRate)
	{
		m_localScaleRate = scaleRate;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}
	// ローカル回転を設定
	void Transform2D::setLocalRotationDeg(float rotationDeg)
	{
		m_localRotationDeg = rotationDeg;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}

	// 新しいローカル行列を指定して自身のローカルのトランスフォームを更新する
	void Transform2D::updateLocalTransform(const Matrix3 & newLocalMat)
	{
		m_localPosition = newLocalMat.calculateTranslation();
		m_localScaleRate = newLocalMat.calculateScale();
		m_localRotationDeg = newLocalMat.calculateRotation();
	}

	// 新しいワールド行列を指定して自身のワールドのトランスフォームを更新する
	void Transform2D::updateWorldTransform(const Matrix3 & newWorldMat)
	{
		m_worldPosition = newWorldMat.calculateTranslation();
		m_worldScaleRate = newWorldMat.calculateScale();
		m_worldRotationDeg = newWorldMat.calculateRotation();
	}

	// 親のTransform2Dを追従するのに使用するワールド行列を取得
	Matrix3 Transform2D::calculateParentTraceUseMat()
	{
		auto parentTransform2D = findParentTransform2D();

		if (!isTransformParentCheck(parentTransform2D)) return Matrix3::identity;

		Matrix3 traceUseMatrix = Matrix3::identity;

		if ((m_traceType & TRACE_PARENT_SCALE) != 0)
		{
			traceUseMatrix *= Matrix3::createScale(parentTransform2D->getWorldScaleRate());
		}

		if ((m_traceType & TRACE_PARENT_ROTATION) != 0)
		{
			traceUseMatrix *= Matrix3::createRotation(parentTransform2D->getWorldRotationDeg());
		}

		if ((m_traceType & TRACE_PARENT_POS) != 0)
		{
			traceUseMatrix *= Matrix3::createTranslation(parentTransform2D->getWorldPosition());
		}
		return traceUseMatrix;
	}

	// 親のTransform2Dを取得
	CfpPtr<Transform2D> Transform2D::findParentTransform2D() const
	{
		CfpPtr<GameObject> parent = getGameObject()->getParent();
		if (parent.isNull()) return CfpPtr<Transform2D>();
		return parent->getComponent<Transform2D>();
	}

	// 全ての子供のTransform2Dを更新する
	void Transform2D::updateAllChildTransform()
	{
		auto childList = getGameObject()->getChildren();

		std::for_each(
			std::begin(childList),
			std::end(childList),
			[this](const auto& node){ updateChildTransform(node); }
		);
	}

	// 指定した子供のTransform2Dを更新する
	void Transform2D::updateChildTransform(CfpPtr<GameObject> child)
	{
		auto childTransform = child->getComponent<Transform2D>();
		if (childTransform.isNull()) return;
		childTransform->updateWorldTransform(
			childTransform->calculateLocalMatrix() *  childTransform->calculateParentTraceUseMat()
		);
		childTransform->updateAllChildTransform();
	}

	// 親のTransform2Dを追従するかを判定する
	bool Transform2D::isTransformParentCheck(CfpPtr<Transform2D> parentTransform2D)
	{
		if (parentTransform2D.isNull())
		{
			if (m_isTransformParent) disableParentTransform();
			return false;
		}
		if (!m_isTransformParent) enableParentTransform();
		return true;
	}

	// 親のTransform2Dの追従を開始
	void Transform2D::enableParentTransform()
	{
		m_isTransformParent = true;
		auto parentTraceUseMat = calculateParentTraceUseMat();
		updateLocalTransform(calculateLocalMatrix() * Matrix3::calculateInvert(parentTraceUseMat));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat);
		
		findAndUpdateRootTransform(this);
	}

	// 親のTransform2Dの追従を終了
	void Transform2D::disableParentTransform()
	{
		m_isTransformParent = false;
		updateLocalTransform(calculateWorldMatrix());
		updateAllChildTransform();
	}

	// 大元のTransformから全ての子供を更新する（生ポインタ版）
	void Transform2D::findAndUpdateRootTransform(Transform2D* curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform2D();

		if (curParentTransform.isNull())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}

	// 大元のTransformから全ての子供を更新する（CfpPtr版）
	void Transform2D::findAndUpdateRootTransform(CfpPtr<Transform2D> curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform2D();

		if (curParentTransform.isNull())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}
}
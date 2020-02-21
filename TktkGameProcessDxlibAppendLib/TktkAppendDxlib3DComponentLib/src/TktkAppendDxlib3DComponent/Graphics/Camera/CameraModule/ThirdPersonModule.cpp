#include "TktkAppendDxlib3DComponent/Graphics/Camera/CameraModule/ThirdPersonModule.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Vector2.h>
#include <TktkMath/Matrix4.h>
#include <TktkMath/Quaternion.h>

#include <iostream>

namespace tktk
{
	ThirdPersonModule::ThirdPersonModule(
		GameObjectPtr target,
		const Vector3&  targetRelativeLookAtPos,
		const Vector3&  relativePos
	)
		: m_target(target)
		, m_targetRelativeLookAtPos(targetRelativeLookAtPos)
		, m_relativePos(relativePos)
	{
	}

	void ThirdPersonModule::start()
	{
		auto selfTransform = getComponent<Transform3D>();

		if (selfTransform.isNull())
		{
			throw std::runtime_error("ThirdPersonModule not found self Transform3D");
		}

		m_selfTransform = selfTransform;
	}

	void ThirdPersonModule::afterCollide()
	{
		if (m_selfTransform.isNull())
		{
			throw std::runtime_error("ThirdPersonModule not found self Transform3D");
		}

		Vector3 targetPos = Vector3::zero;
		Vector3 targetRotation = Vector3::zero;

		if (!m_target.isNull())
		{
			auto targetTransform = m_target->getComponent<Transform3D>();

			if (targetTransform.isNull())
			{
				throw std::runtime_error("ThirdPersonModule not found target Transform3D");
			}

			targetPos = targetTransform->getWorldPosition();
			targetRotation = targetTransform->calculateWorldEulerAngles();
		}

		Vector3 cameraToTarget = m_targetRelativeLookAtPos - m_relativePos;

		float rotaX = Vector2::signedAngle(Vector2::right, Vector2(Vector2(cameraToTarget.x, cameraToTarget.z).length(), cameraToTarget.y));

		float roteY = Vector2::signedAngle(Vector2::down, Vector2(cameraToTarget.x, cameraToTarget.z));

		Matrix4 rotateMat
			= Matrix4::createRotationX(rotaX)
			* Matrix4::createRotationY(-roteY)
			* Matrix4::createTranslation(m_relativePos)
			* Matrix4::createFromYawPitchRoll(targetRotation.y, targetRotation.x, targetRotation.z);

		Vector3 selfPos = rotateMat.calculateTranslation() + targetPos;
		m_selfTransform->setLocalPosition(selfPos);

		m_selfTransform->setLocalEulerAngles(rotateMat.calculateRotation().calculateEulerAngle());
	}

	void ThirdPersonModule::setTarget(GameObjectPtr target)
	{
		m_target = target;
	}

	void ThirdPersonModule::setTargetRelativeLookAtPos(const Vector3 & targetRelativeLookAtPos)
	{
		m_targetRelativeLookAtPos = targetRelativeLookAtPos;
	}

	void ThirdPersonModule::setRelativePos(const Vector3 & relativePos)
	{
		m_relativePos = relativePos;
	}
}
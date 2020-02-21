#include "TktkAppendDxlib3DComponent/Graphics/Camera/BasicCamera.h"

#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <DxLib.h>
#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"

namespace tktk
{
	BasicCamera::BasicCamera(
		float drawPriority,
		float initCameraFov,
		float initCameraAspectRate,
		float initCameraDrawingRangeNear,
		float initCameraDrawingRangeFar
	)
		: ComponentBase(drawPriority)
		, m_cameraFov(initCameraFov)
		, m_cameraAspectRate(initCameraAspectRate)
		, m_cameraDrawingRangeNear(initCameraDrawingRangeNear)
		, m_cameraDrawingRangeFar(initCameraDrawingRangeFar)
	{
	}

	void BasicCamera::afterCollide()
	{
		if (m_transform3D.isNull())
		{
			auto transform3D = getComponent<Transform3D>();

			if (transform3D.isNull()) return;

			m_transform3D = transform3D;
		}
		Sound3DManager::setSoundListenerPosition(
			m_transform3D->getWorldPosition(),
			m_transform3D->calculateWorldMatrix().calculateForwardLH(),
			m_transform3D->calculateWorldMatrix().calculateUp()
		);
	}

	void BasicCamera::draw() const
	{
		DxLib::SetCameraViewMatrix(DXConverter::toMATRIX(calculateViewMatrix()));
		DxLib::SetupCamera_ProjectionMatrix(DXConverter::toMATRIX(calculateProjectionMatrix()));
	}

	Matrix4 BasicCamera::calculateViewMatrix() const
	{
		auto cameraWorldMat = m_transform3D->calculateWorldMatrix();

		return Matrix4::createLookAtLH(
			m_transform3D->getWorldPosition(), 
			m_transform3D->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()
		);
	}

	Matrix4 BasicCamera::calculateProjectionMatrix() const
	{
		return Matrix4::createPerspectiveFieldOfViewLH(
			m_cameraFov,
			m_cameraAspectRate,
			m_cameraDrawingRangeNear,
			m_cameraDrawingRangeFar
		);
	}

	float BasicCamera::getCameraFov() const
	{
		return m_cameraFov;
	}

	float BasicCamera::getCameraAspectRate() const
	{
		return m_cameraAspectRate;
	}

	float BasicCamera::getCameraDrawingRangeNear() const
	{
		return m_cameraDrawingRangeNear;
	}

	float BasicCamera::getCameraDrawingRangeFar() const
	{
		return m_cameraDrawingRangeFar;
	}

	void BasicCamera::setCameraFov(float cameraFov)
	{
		m_cameraFov = cameraFov;
	}

	void BasicCamera::setCameraAspectRate(float cameraAspectRate)
	{
		m_cameraAspectRate = cameraAspectRate;
	}

	void BasicCamera::setCameraDrawingRangeNear(float cameraDrawingRangeNear)
	{
		m_cameraDrawingRangeNear = cameraDrawingRangeNear;
	}

	void BasicCamera::setCameraDrawingRangeFar(float cameraDrawingRangeFar)
	{
		m_cameraDrawingRangeFar = cameraDrawingRangeFar;
	}
}
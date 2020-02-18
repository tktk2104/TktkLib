#include "TktkAppendDirectX11Component/Graphics/Camera/SimpleCamera.h"

#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Camera/Camera.h"

namespace tktk
{
	SimpleCamera::SimpleCamera(int cameraId, float cameraFov, float cameraNear, float cameraFar)
		: m_cameraId(cameraId)
		, m_cameraFov(cameraFov)
		, m_cameraNear(cameraNear)
		, m_cameraFar(cameraFar)
	{
	}

	SimpleCamera::~SimpleCamera()
	{
	}

	void SimpleCamera::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("SimpleCamera Transform3D not found");
		}

		Matrix4 cameraWorldMat = m_transform->calculateWorldMatrix();

		Matrix4 viewMat = Matrix4::createLookAtLH(
			m_transform->getWorldPosition(),
			m_transform->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()
		);

		Matrix4 projMat = Matrix4::createPerspectiveFieldOfViewLH(
			m_cameraFov,
			tktk::Window::getWindowSize().x / tktk::Window::getWindowSize().y,
			m_cameraNear,
			m_cameraFar
		);

		tktk::Camera::create(m_cameraId, viewMat, projMat);
	}

	void SimpleCamera::afterCollide()
	{
		Matrix4 cameraWorldMat = m_transform->calculateWorldMatrix();

		CameraData* cameraDataPtr = Camera::getDataPtr(m_cameraId);

		*cameraDataPtr->getViewMatrixPtr() = Matrix4::createLookAtLH(
			m_transform->getWorldPosition(),
			m_transform->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()
		);

		*cameraDataPtr->getProjectionMatrixPtr() = Matrix4::createPerspectiveFieldOfViewLH(
			m_cameraFov,
			tktk::Window::getWindowSize().x / tktk::Window::getWindowSize().y,
			m_cameraNear,
			m_cameraFar
		);
	}

	float * SimpleCamera::getCameraFovPtr()
	{
		return &m_cameraFov;
	}

	float * SimpleCamera::getCameraNearPtr()
	{
		return &m_cameraNear;
	}

	float * SimpleCamera::getCameraFarPtr()
	{
		return &m_cameraFar;
	}
}
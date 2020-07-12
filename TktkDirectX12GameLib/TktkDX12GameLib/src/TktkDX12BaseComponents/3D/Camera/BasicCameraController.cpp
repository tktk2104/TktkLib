#include "TktkDX12BaseComponents/3D/Camera/BasicCameraController.h"

namespace tktk
{
	BasicCameraController::BasicCameraController(
		unsigned int cameraId,
		float camerafov,
		float cameraAspect,
		float cameraNear,
		float cameraFar
	)
		: m_cameraId(cameraId)
		, m_cameraFov(camerafov)
		, m_cameraAspect(cameraAspect)
		, m_cameraNear(cameraNear)
		, m_cameraFar(cameraFar)
	{
	}

	void BasicCameraController::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		updateCameraMat();
	}

	void BasicCameraController::afterCollide()
	{
		updateCameraMat();
	}

	void BasicCameraController::updateCameraMat()
	{
		auto cameraWorldMat = m_transform->calculateWorldMatrix();

		auto viewMat = tktkMath::Matrix4::createLookAtLH(
			m_transform->getWorldPosition(),
			m_transform->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()
		);
		DX12GameManager::setViewMatrix(m_cameraId, viewMat);

		auto projectionMat = tktkMath::Matrix4::createPerspectiveFieldOfViewLH(
			m_cameraFov,
			m_cameraAspect,
			m_cameraNear,
			m_cameraFar
		);
		DX12GameManager::setProjectionMatrix(m_cameraId, projectionMat);
	}
}
#include "TktkDX12BaseComponents/3D/Camera/OrthographicCameraController.h"

namespace tktk
{
	OrthographicCameraController::OrthographicCameraController(
		unsigned int cameraId,
		float cameraWidth,
		float cameraHeight,
		float cameraNear,
		float cameraFar
	)
		: m_cameraId(cameraId)
		, m_cameraWidth(cameraWidth)
		, m_cameraHeight(cameraHeight)
		, m_cameraNear(cameraNear)
		, m_cameraFar(cameraFar)
	{
	}

	void OrthographicCameraController::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		updateCameraMat();
	}

	void OrthographicCameraController::afterCollide()
	{
		updateCameraMat();
	}

	void OrthographicCameraController::updateCameraMat()
	{
		auto cameraWorldMat = m_transform->calculateWorldMatrix();

		auto viewMat = tktkMath::Matrix4::createLookAtLH(
			m_transform->getWorldPosition(),
			m_transform->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()//tktkMath::vec3Up
		);
		DX12GameManager::setViewMatrix(m_cameraId, viewMat);

		auto projectionMat = tktkMath::Matrix4::createOrthographicLH(
			m_cameraWidth,
			m_cameraHeight,
			m_cameraNear,
			m_cameraFar
		);
		DX12GameManager::setProjectionMatrix(m_cameraId, projectionMat);
	}
}
#include "TktkDirectX11Wrapper/Graphics/Camera/Camera.h"

#include "TktkDirectX11Wrapper/Graphics/Camera/CameraManager.h"

namespace tktk
{
	void Camera::create(int id, const Matrix4 & viewMatrix, const Matrix4 & projectionMatrix)
	{
		CameraManager::create(id, viewMatrix, projectionMatrix);
	}

	void Camera::erase(int id)
	{
		CameraManager::erase(id);
	}

	CameraData * Camera::getDataPtr(int id)
	{
		return CameraManager::getDataPtr(id);
	}
}
#include "TktkDirectX11Wrapper/Graphics/Camera/Camera.h"

#include "TktkDirectX11Wrapper/Graphics/Camera/CameraManager.h"

namespace tktk
{
	void Camera::createImpl(int id, const Matrix4 & viewMatrix, const Matrix4 & projectionMatrix)
	{
		CameraManager::create(id, viewMatrix, projectionMatrix);
	}

	void Camera::eraseImpl(int id)
	{
		CameraManager::erase(id);
	}

	CameraData * Camera::getDataPtrImpl(int id)
	{
		return CameraManager::getDataPtr(id);
	}
}
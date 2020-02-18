#include "TktkDirectX11Wrapper/Graphics/Camera/CameraManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<CameraAssets> CameraManager::m_assetsPtr;

	void CameraManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new CameraAssets());
	}

	void CameraManager::create(int id, const Matrix4 & viewMatrix, const Matrix4 & projectionMatrix)
	{
		m_assetsPtr->create(id, viewMatrix, projectionMatrix);
	}

	void CameraManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void CameraManager::clear()
	{
		m_assetsPtr->clear();
	}

	CameraData * CameraManager::getDataPtr(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}
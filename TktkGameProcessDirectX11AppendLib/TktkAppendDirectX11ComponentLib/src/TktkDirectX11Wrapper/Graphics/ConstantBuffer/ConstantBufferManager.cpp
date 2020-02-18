#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<ConstantBufferAssets> ConstantBufferManager::m_assetsPtr;

	void ConstantBufferManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new ConstantBufferAssets());
	}

	void ConstantBufferManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	ConstantBufferData * ConstantBufferManager::getDataPtr(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}

	void ConstantBufferManager::addParamLocation(int id, int locationType, unsigned int locationFromBufferTop)
	{
		m_assetsPtr->addParamLocation(id, locationType, locationFromBufferTop);
	}
}
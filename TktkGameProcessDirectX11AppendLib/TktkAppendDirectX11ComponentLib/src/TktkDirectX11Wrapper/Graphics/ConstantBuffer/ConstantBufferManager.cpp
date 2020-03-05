#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<ConstantBufferAssets> ConstantBufferManager::m_assetsPtr;

	void ConstantBufferManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<ConstantBufferAssets>(true);
	}

	void ConstantBufferManager::clear()
	{
		m_assetsPtr->clear();
	}

	void ConstantBufferManager::createImpl(int id, SafetyVoidPtr && data)
	{
		m_assetsPtr->create(id, std::move(data));
	}

	void ConstantBufferManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	ConstantBufferData * ConstantBufferManager::getDataPtrImpl(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}
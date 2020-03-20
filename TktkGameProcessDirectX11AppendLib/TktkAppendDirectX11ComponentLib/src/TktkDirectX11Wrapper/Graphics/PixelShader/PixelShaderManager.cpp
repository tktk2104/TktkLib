#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<PixelShaderAssets> PixelShaderManager::m_assetsPtr;

	void PixelShaderManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<PixelShaderAssets>(true);
	}

	void PixelShaderManager::clear()
	{
		m_assetsPtr->clear();
	}

	void PixelShaderManager::loadImpl(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName)
	{
		m_assetsPtr->load(id, useConstantBufferIdArray, fileName);
	}

	void PixelShaderManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const PixelShaderData & PixelShaderManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}
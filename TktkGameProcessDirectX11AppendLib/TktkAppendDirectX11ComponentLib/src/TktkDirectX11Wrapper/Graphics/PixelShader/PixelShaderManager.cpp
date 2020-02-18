#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<PixelShaderAssets> PixelShaderManager::m_assetsPtr;

	void PixelShaderManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new PixelShaderAssets());
	}

	void PixelShaderManager::load(int id, int useConstantBufferId, const std::string & fileName)
	{
		m_assetsPtr->load(id, useConstantBufferId, fileName);
	}

	void PixelShaderManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void PixelShaderManager::clear()
	{
		m_assetsPtr->clear();
	}

	const PixelShaderData & PixelShaderManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<VertexShaderAssets> VertexShaderManager::m_assetsPtr;

	void VertexShaderManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new VertexShaderAssets());
	}

	void VertexShaderManager::clear()
	{
		m_assetsPtr->clear();
	}

	void VertexShaderManager::loadImpl(int id, int useConstantBufferId, const std::string & fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
	{
		m_assetsPtr->load(id, useConstantBufferId, fileName, vertexLayout);
	}

	void VertexShaderManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const VertexShaderData & VertexShaderManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}
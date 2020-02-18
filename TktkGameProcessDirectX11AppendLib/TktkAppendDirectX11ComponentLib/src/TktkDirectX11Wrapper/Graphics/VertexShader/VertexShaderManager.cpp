#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<VertexShaderAssets> VertexShaderManager::m_assetsPtr;

	void VertexShaderManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new VertexShaderAssets());
	}

	void VertexShaderManager::load(int id, int useConstantBufferId, const std::string & fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
	{
		m_assetsPtr->load(id, useConstantBufferId, fileName, vertexLayout);
	}

	void VertexShaderManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void VertexShaderManager::clear()
	{
		m_assetsPtr->clear();
	}

	const VertexShaderData & VertexShaderManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}
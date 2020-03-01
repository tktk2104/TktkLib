#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"

namespace tktk
{
	void VertexShader::loadImpl(int id, int useConstantBufferId, const std::string & fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
	{
		if (id <= 0)
		{
			throw std::runtime_error("VertexShaderId Fraud Value");
		}
		VertexShaderManager::load(id, useConstantBufferId, fileName, vertexLayout);
	}

	void VertexShader::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("VertexShaderId Fraud Value");
		}
		VertexShaderManager::erase(id);
	}

	const VertexShaderData & VertexShader::getDataImpl(int id)
	{
		return VertexShaderManager::getData(id);
	}
}
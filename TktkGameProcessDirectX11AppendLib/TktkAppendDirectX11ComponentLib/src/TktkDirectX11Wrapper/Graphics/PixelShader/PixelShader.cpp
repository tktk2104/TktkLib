#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"

namespace tktk
{
	void PixelShader::loadImpl(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("PixelShaderId Fraud Value");
		}
		PixelShaderManager::loadImpl(id, useConstantBufferIdArray, fileName);
	}

	void PixelShader::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("PixelShaderId Fraud Value");
		}
		PixelShaderManager::erase(id);
	}

	const PixelShaderData & PixelShader::getDataImpl(int id)
	{
		return PixelShaderManager::getData(id);
	}
}
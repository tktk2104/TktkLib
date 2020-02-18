#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"

namespace tktk
{
	void PixelShader::load(int id, int useConstantBufferId, const std::string & fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("PixelShaderId Fraud Value");
		}
		PixelShaderManager::load(id, useConstantBufferId, fileName);
	}

	void PixelShader::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("PixelShaderId Fraud Value");
		}
		PixelShaderManager::erase(id);
	}

	const PixelShaderData & PixelShader::getData(int id)
	{
		return PixelShaderManager::getData(id);
	}
}
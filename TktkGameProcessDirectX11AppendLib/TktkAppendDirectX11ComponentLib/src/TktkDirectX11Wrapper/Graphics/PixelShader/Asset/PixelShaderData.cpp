#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/PixelShaderData.h"

#include <vector>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	inline void getShaderByteArray(std::vector<char>* byteArray, const std::string& fileName);
	inline ID3D11PixelShader* createPixelShader(const std::vector<char>& byteArray);

	PixelShaderData::PixelShaderData(int useConstantBufferId, const std::string & fileName)
		: m_useConstantBufferId(useConstantBufferId)
	{
		std::vector<char> byteArray;

		getShaderByteArray(&byteArray, fileName);

		m_shaderPtr = createPixelShader(byteArray);
	}

	PixelShaderData::~PixelShaderData()
	{
		if (m_shaderPtr != nullptr)
		{
			m_shaderPtr->Release();
		}
	}

	void PixelShaderData::beginShader() const
	{
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(m_useConstantBufferId);
		ID3D11Buffer* constantBuffer = constantBufferData->getBufferPtr();

		Screen::getDeviceContextPtr()->PSSetConstantBuffers(0, 1, &constantBuffer);
		Screen::getDeviceContextPtr()->PSSetShader(m_shaderPtr, NULL, 0);
	}

	int PixelShaderData::getUseConstantBufferId() const
	{
		return m_useConstantBufferId;
	}

	ID3D11PixelShader * PixelShaderData::getShaderPtr() const
	{
		return m_shaderPtr;
	}

	void getShaderByteArray(std::vector<char>* byteArray, const std::string & fileName)
	{
		std::FILE* fp;

		int ret = fopen_s(&fp, fileName.c_str(), "rb");

		if (ret != 0)
		{
			throw std::runtime_error("load pixelShader error");
		}

		fseek(fp, 0, SEEK_END);
		byteArray->resize(ftell(fp));
		fseek(fp, 0, SEEK_SET);

		fread(byteArray->data(), byteArray->size(), 1, fp);
		fclose(fp);
	}

	ID3D11PixelShader * createPixelShader(const std::vector<char>& byteArray)
	{
		ID3D11PixelShader* result = nullptr;

		Screen::getDevicePtr()->CreatePixelShader(byteArray.data(), byteArray.size(), nullptr, &result);

		return result;
	}
}
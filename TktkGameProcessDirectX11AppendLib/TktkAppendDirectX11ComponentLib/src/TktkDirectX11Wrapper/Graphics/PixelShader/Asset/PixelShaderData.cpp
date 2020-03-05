#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/PixelShaderData.h"

#include <vector>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	inline void getShaderByteArray(std::vector<char>* byteArray, const std::string& fileName);
	inline ID3D11PixelShader* createPixelShader(const std::vector<char>& byteArray);

	PixelShaderData::PixelShaderData(const std::vector<int>& useConstantBufferIdArray, const std::string & fileName)
		: m_useConstantBufferIdArray(useConstantBufferIdArray)
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
		std::vector<ID3D11Buffer*> useConstantBufferDataArray;
		useConstantBufferDataArray.reserve(m_useConstantBufferIdArray.size());

		for (int useConstantBufferId : m_useConstantBufferIdArray)
		{
			useConstantBufferDataArray.push_back(ConstantBuffer::getDataPtr(useConstantBufferId)->getBufferPtr());
		}

		Screen::getDeviceContextPtr()->PSSetConstantBuffers(0, useConstantBufferDataArray.size(), useConstantBufferDataArray.data());
		Screen::getDeviceContextPtr()->PSSetShader(m_shaderPtr, NULL, 0);
	}

	const std::vector<int>& PixelShaderData::getUseConstantBufferIdArray() const
	{
		return m_useConstantBufferIdArray;
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
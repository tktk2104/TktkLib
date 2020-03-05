#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/VertexShaderData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	inline void getShaderByteArray(std::vector<char>* byteArray, const std::string& fileName);
	inline ID3D11VertexShader* createVertexShader(const std::vector<char>& byteArray);
	inline ID3D11InputLayout* createVertexLayout(const std::vector<char>& byteArray, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);

	VertexShaderData::VertexShaderData(
		const std::vector<int> & useConstantBufferIdArray,
		const std::string & fileName,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
	)
		: m_useConstantBufferIdArray(useConstantBufferIdArray)
	{
		std::vector<char> byteArray;
		getShaderByteArray(&byteArray, fileName);

		m_vertexShaderPtr = createVertexShader(byteArray);
		m_vertexLayoutPtr = createVertexLayout(byteArray, vertexLayout);
	}

	VertexShaderData::~VertexShaderData()
	{
		if (m_vertexShaderPtr != nullptr)
		{
			m_vertexShaderPtr->Release();
		}

		if (m_vertexLayoutPtr != nullptr)
		{
			m_vertexLayoutPtr->Release();
		}
	}

	void VertexShaderData::beginVertexShader() const
	{
		std::vector<ID3D11Buffer*> useConstantBufferDataArray;
		useConstantBufferDataArray.reserve(m_useConstantBufferIdArray.size());

		for (int useConstantBufferId : m_useConstantBufferIdArray)
		{
			useConstantBufferDataArray.push_back(ConstantBuffer::getDataPtr(useConstantBufferId)->getBufferPtr());
		}

		Screen::getDeviceContextPtr()->VSSetConstantBuffers(0, useConstantBufferDataArray.size(), useConstantBufferDataArray.data());
		Screen::getDeviceContextPtr()->VSSetShader(m_vertexShaderPtr, NULL, 0);
		Screen::getDeviceContextPtr()->IASetInputLayout(m_vertexLayoutPtr);
	}

	const std::vector<int>& VertexShaderData::getUseConstantBufferIdArray() const
	{
		return m_useConstantBufferIdArray;
	}

	ID3D11VertexShader * VertexShaderData::getShaderPtr() const
	{
		return m_vertexShaderPtr;
	}

	ID3D11InputLayout * VertexShaderData::getVertexLayoutPtr() const
	{
		return m_vertexLayoutPtr;
	}

	void getShaderByteArray(std::vector<char>* byteArray, const std::string & fileName)
	{
		std::FILE* fp;

		int ret = fopen_s(&fp, fileName.c_str(), "rb");

		if (ret != 0)
		{
			throw std::runtime_error("load vertexShader error");
		}

		fseek(fp, 0, SEEK_END);
		byteArray->resize(ftell(fp));
		fseek(fp, 0, SEEK_SET);

		fread(byteArray->data(), byteArray->size(), 1, fp);
		fclose(fp);
	}

	ID3D11VertexShader * createVertexShader(const std::vector<char>& byteArray)
	{
		ID3D11VertexShader* result = nullptr;

		Screen::getDevicePtr()->CreateVertexShader(
			byteArray.data(),
			byteArray.size(),
			nullptr,
			&result
		);
		return result;
	}

	ID3D11InputLayout * createVertexLayout(const std::vector<char>& byteArray, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
	{
		ID3D11InputLayout* result = nullptr;

		Screen::getDevicePtr()->CreateInputLayout(
			vertexLayout.data(),
			vertexLayout.size(),
			byteArray.data(),
			byteArray.size(),
			&result
		);
		return result;
	}
}
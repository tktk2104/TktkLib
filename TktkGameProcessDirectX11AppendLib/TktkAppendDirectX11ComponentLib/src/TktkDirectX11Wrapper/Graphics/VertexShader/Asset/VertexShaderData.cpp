#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/VertexShaderData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	inline void getShaderByteArray(std::vector<char>* byteArray, const std::string& fileName);
	inline ID3D11VertexShader* createVertexShader(const std::vector<char>& byteArray);
	inline ID3D11InputLayout* createVertexLayout(const std::vector<char>& byteArray, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);

	VertexShaderData::VertexShaderData(
		int useConstantBufferId,
		const std::string & fileName,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
	)
		: m_useConstantBufferId(useConstantBufferId)
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
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(m_useConstantBufferId);
		ID3D11Buffer* constantBuffer = constantBufferData->getBufferPtr();

		Screen::getDeviceContextPtr()->VSSetConstantBuffers(0, 1, &constantBuffer);
		Screen::getDeviceContextPtr()->VSSetShader(m_vertexShaderPtr, NULL, 0);
		Screen::getDeviceContextPtr()->IASetInputLayout(m_vertexLayoutPtr);
	}

	int VertexShaderData::getUseConstantBufferId() const
	{
		return m_useConstantBufferId;
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
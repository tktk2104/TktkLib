#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/Texture2DData.h"

#include <stdexcept>
#include <TktkBinaryProcessing/BinaryFileReader.h>
#include <TktkTextProcessing/ExtensionGetter.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Utility/lodepng.h"
#include "TktkDirectX11Wrapper/Utility/lodedds.h"

namespace tktk
{
	Texture2DData::Texture2DData(
		unsigned char * data,
		unsigned int dataSize
	)
	{
		ID3D11Resource* resource;

		lodedds::load(
			Screen::getDevicePtr(),
			data,
			dataSize,
			&resource,
			&m_shaderResouceViewPtr,
			0
		);
	}

	Texture2DData::Texture2DData(const std::string & fileName)
	{
		std::string extension;
		ExtensionGetter::get(fileName, &extension);

		if (extension == "png")
		{
			std::vector<unsigned char> image;
			auto error = lodepng::decode(image, m_width, m_height, fileName);
			if (error != 0)
			{
				throw std::runtime_error("can not open" + fileName);
			}
			createTextrue2D(image);

			createShaderResourceView();

			createSamplerState();
		}
		else if (extension == "dds")
		{
			std::vector<unsigned char> image;

			BinaryFileReader::fileRead(fileName, &image);

			ID3D11Resource* resource;

			lodedds::load(
				Screen::getDevicePtr(),
				image.data(),
				image.size(),
				&resource,
				&m_shaderResouceViewPtr,
				0
			);
		}
	}

	Texture2DData::~Texture2DData()
	{
		if (m_texturePtr != nullptr)
		{
			m_texturePtr->Release();
		}

		if (m_shaderResouceViewPtr != nullptr)
		{
			m_shaderResouceViewPtr->Release();
		}

		if (m_samplerPtr != nullptr)
		{
			m_samplerPtr->Release();
		}
	}

	ID3D11Texture2D * Texture2DData::getTexture2DPtr() const
	{
		return m_texturePtr;
	}

	ID3D11ShaderResourceView * Texture2DData::getShaderResourceViewPtr() const
	{
		return m_shaderResouceViewPtr;
	}

	ID3D11SamplerState * Texture2DData::getSamplerStatePtr() const
	{
		return m_samplerPtr;
	}

	unsigned int Texture2DData::width() const
	{
		return m_width;
	}

	unsigned int Texture2DData::height() const
	{
		return m_height;
	}

	void Texture2DData::createTextrue2D(const std::vector<unsigned char> & image)
	{
		D3D11_TEXTURE2D_DESC texture2dDesc{};
		texture2dDesc.Width = m_width;
		texture2dDesc.Height = m_height;
		texture2dDesc.MipLevels = 1;
		texture2dDesc.ArraySize = 1;
		texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture2dDesc.SampleDesc.Count = 1;
		texture2dDesc.SampleDesc.Quality = 0;
		texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
		texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texture2dDesc.CPUAccessFlags = 0;
		texture2dDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subrescorceData{};
		subrescorceData.pSysMem = image.data();
		subrescorceData.SysMemPitch = m_width * 4;
		subrescorceData.SysMemSlicePitch = m_width * m_height * 4;

		Screen::getDevicePtr()->CreateTexture2D(&texture2dDesc, &subrescorceData, &m_texturePtr);

	}

	void Texture2DData::createShaderResourceView()
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResouceViewDesc{};
		shaderResouceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		shaderResouceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResouceViewDesc.Texture2D.MipLevels = 1;
		
		Screen::getDevicePtr()->CreateShaderResourceView(m_texturePtr, &shaderResouceViewDesc, &m_shaderResouceViewPtr);
	}

	void Texture2DData::createSamplerState()
	{
		D3D11_SAMPLER_DESC samplerDesc{};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		Screen::getDevicePtr()->CreateSamplerState(&samplerDesc, &m_samplerPtr);
	}
}
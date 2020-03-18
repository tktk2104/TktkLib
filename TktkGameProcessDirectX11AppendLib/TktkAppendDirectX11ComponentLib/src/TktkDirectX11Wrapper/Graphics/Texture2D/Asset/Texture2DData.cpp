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
		Texture2DBindFlag bindFlag,
		const std::vector<D3D11_SUBRESOURCE_DATA> & subrescorceDataArray,
		unsigned int width,
		unsigned int height,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		bool isCubeMap
	)
		: m_width(width)
		, m_height(height)
	{
		D3D11_TEXTURE2D_DESC texture2dDesc{};
		texture2dDesc.Width = width;
		texture2dDesc.Height = height;
		texture2dDesc.MipLevels = mipCount;
		texture2dDesc.ArraySize = arraySize;
		texture2dDesc.Format = format;
		texture2dDesc.SampleDesc.Count = 1U;
		texture2dDesc.SampleDesc.Quality = 0U;
		texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
		texture2dDesc.BindFlags = static_cast<unsigned int>(bindFlag);
		texture2dDesc.CPUAccessFlags = 0U;
		texture2dDesc.MiscFlags = (isCubeMap) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0U;

		Screen::getDevicePtr()->CreateTexture2D(&texture2dDesc, subrescorceDataArray.data(), &m_texturePtr);

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResouceViewDesc{};
		shaderResouceViewDesc.Format = format;

		if (isCubeMap)
		{
			if (arraySize > 6U)
			{
				shaderResouceViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
				shaderResouceViewDesc.TextureCubeArray.MipLevels = mipCount;
				shaderResouceViewDesc.TextureCubeArray.NumCubes = arraySize / 6U;
			}
			else
			{
				shaderResouceViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
				shaderResouceViewDesc.TextureCube.MipLevels = mipCount;
			}
		}
		else
		{
			if (arraySize > 1U)
			{
				shaderResouceViewDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DARRAY;
				shaderResouceViewDesc.Texture2DArray.MipLevels = mipCount;
				shaderResouceViewDesc.Texture2DArray.ArraySize = arraySize;
			}
			else
			{
				shaderResouceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				shaderResouceViewDesc.Texture2D.MipLevels = mipCount;
			}
		}

		Screen::getDevicePtr()->CreateShaderResourceView(m_texturePtr, &shaderResouceViewDesc, &m_shaderResouceViewPtr);

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
}
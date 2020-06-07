#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/TextureBuffer/TextureBufferData.h"

namespace tktk
{
	TextureBufferData::TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureSize = { static_cast<float>(dataParam.width), static_cast<float>(dataParam.height), 1.0f };

		{
			m_srvInitParam.format = formatParam.format;

			if (formatParam.arraySize > 1U)
			{
				switch (formatParam.resourceDimension)
				{
				case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

					// TODO : CubeMap�̏ꍇ�̏����������
					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
					break;
				}
			}
			else
			{
				switch (formatParam.resourceDimension)
				{
				case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

					// TODO : CubeMap�̏ꍇ�̏����������
					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE3D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
					break;
				}
			}
			m_srvInitParam.mostDetailedMip = 0;
			m_srvInitParam.mipLevels = formatParam.mipLevels;
			m_srvInitParam.firstArraySlice = 0;
			m_srvInitParam.arraySize = formatParam.arraySize;
			m_srvInitParam.planeSlice = 0;
			m_srvInitParam.minLodClamp = 0.0f;
		}


		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		heapProp.CreationNodeMask = 0;
		heapProp.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = formatParam.resourceDimension;
		resDesc.Format = formatParam.format;
		resDesc.Width = dataParam.width;
		resDesc.Height = dataParam.height;
		resDesc.DepthOrArraySize = formatParam.arraySize;
		resDesc.SampleDesc.Count = formatParam.sampleDescCount;
		resDesc.SampleDesc.Quality = formatParam.sampleDescQuality;
		resDesc.MipLevels = formatParam.mipLevels;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(&m_textureBuffer)
		);

		m_textureBuffer->WriteToSubresource(
			0,
			nullptr,
			dataParam.textureData.data(),
			dataParam.width * 4,
			dataParam.textureData.size()
		);
	}

	TextureBufferData::TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureSize = { static_cast<float>(dataParam.width), static_cast<float>(dataParam.height), 1.0f };

		{
			m_srvInitParam.format = formatParam.format;

			if (formatParam.arraySize > 1U)
			{
				switch (formatParam.resourceDimension)
				{
				case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

					// TODO : CubeMap�̏ꍇ�̏����������
					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
					break;
				}
			}
			else
			{
				switch (formatParam.resourceDimension)
				{
				case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

					// TODO : CubeMap�̏ꍇ�̏����������
					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					break;

				case D3D12_RESOURCE_DIMENSION_TEXTURE3D:

					m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
					break;
				}
			}
			m_srvInitParam.mostDetailedMip = 0;
			m_srvInitParam.mipLevels = formatParam.mipLevels;
			m_srvInitParam.firstArraySlice = 0;
			m_srvInitParam.arraySize = formatParam.arraySize;
			m_srvInitParam.planeSlice = 0;
			m_srvInitParam.minLodClamp = 0.0f;
		}

		// CPU�A�N�Z�X�ɓ��������q�[�v�����iCPU����e�N�X�`���f�[�^���R�s�[���鎞�Ɏg�p����j
		{
			D3D12_HEAP_PROPERTIES uploadHeapProp{};
			uploadHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			uploadHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadHeapProp.CreationNodeMask = 0;
			uploadHeapProp.VisibleNodeMask = 0;

			// ���ԃo�b�t�@�Ȃ̂Ńo�b�t�@�͂����̃o�C�i���f�[�^�̉�Ƃ��ĉ��߂�����
			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = dataParam.textureData.size();
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			device->CreateCommittedResource(
				&uploadHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_uploadBuff)
			);

			// �e�N�X�`����CPU�A�N�Z�X�����q�[�v�ɃR�s�[����
			unsigned char* mapForImg{ nullptr };
			m_uploadBuff->Map(0, nullptr, (void**)&mapForImg);
			std::copy_n(dataParam.textureData.data(), dataParam.textureData.size(), mapForImg);
			m_uploadBuff->Unmap(0, nullptr);
		}

		// GPU�A�N�Z�X�ɓ��������q�[�v�����i�V�F�[�_�[���g�p����j
		{
			D3D12_HEAP_PROPERTIES texHeapProp{};
			texHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
			texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			texHeapProp.CreationNodeMask = 0;
			texHeapProp.VisibleNodeMask = 0;

			// �V�F�[�_�[���g�p����o�b�t�@�Ȃ̂ł����ƃe�N�X�`���Ƃ��ĉ��߂�����
			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = formatParam.resourceDimension;
			resDesc.Format = formatParam.format;
			resDesc.Width = dataParam.width;
			resDesc.Height = dataParam.height;
			resDesc.DepthOrArraySize = formatParam.arraySize;
			resDesc.MipLevels = formatParam.mipLevels;
			resDesc.SampleDesc.Count = formatParam.sampleDescCount;
			resDesc.SampleDesc.Quality = formatParam.sampleDescQuality;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

			device->CreateCommittedResource(
				&texHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&m_textureBuffer)
			);
		}

		// �R�s�[���́u�t�b�g�v�����g�v�w��
		D3D12_TEXTURE_COPY_LOCATION src{};
		src.pResource = m_uploadBuff;
		src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset = 0;
		src.PlacedFootprint.Footprint.Width = dataParam.width;
		src.PlacedFootprint.Footprint.Height = dataParam.height;
		src.PlacedFootprint.Footprint.Depth = 1;
		src.PlacedFootprint.Footprint.RowPitch = dataParam.width * 4;
		src.PlacedFootprint.Footprint.Format = formatParam.format;

		// �R�s�[��́u�C���f�b�N�X�v�w��
		D3D12_TEXTURE_COPY_LOCATION dst{};
		dst.pResource = m_textureBuffer;
		dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex = 0;

		// GPU�Ԃ̃������̃R�s�[���s��
		commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

		// �e�N�X�`���o�b�t�@�[�̃o���A���u�R�s�[��v��Ԃ���u�V�F�[�_�[���\�[�X�v��ԂɕύX����
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_textureBuffer;
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	TextureBufferData::~TextureBufferData()
	{
		if (m_textureBuffer != nullptr)
		{
			m_textureBuffer->Release();
		}

		if (m_uploadBuff != nullptr)
		{
			m_uploadBuff->Release();
		}
	}

	void TextureBufferData::createShaderResourceView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = m_srvInitParam.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = m_srvInitParam.viewDimension;

		switch (srvDesc.ViewDimension)
		{
		case D3D12_SRV_DIMENSION_TEXTURE1D:

			srvDesc.Texture1D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture1D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture1D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE1DARRAY:

			srvDesc.Texture1DArray.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.Texture1DArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture1DArray.FirstArraySlice		= m_srvInitParam.firstArraySlice;
			srvDesc.Texture1DArray.ArraySize			= m_srvInitParam.arraySize;
			srvDesc.Texture1DArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE2D:

			srvDesc.Texture2D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture2D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture2D.PlaneSlice			= m_srvInitParam.planeSlice;
			srvDesc.Texture2D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE2DARRAY:

			srvDesc.Texture2DArray.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.Texture2DArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture2DArray.FirstArraySlice		= m_srvInitParam.firstArraySlice;
			srvDesc.Texture2DArray.ArraySize			= m_srvInitParam.arraySize;
			srvDesc.Texture2DArray.PlaneSlice			= m_srvInitParam.planeSlice;
			srvDesc.Texture2DArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE3D:

			srvDesc.Texture3D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture3D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture3D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURECUBE:

			srvDesc.TextureCube.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.TextureCube.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.TextureCube.ResourceMinLODClamp = m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURECUBEARRAY:

			srvDesc.TextureCubeArray.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.TextureCubeArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.TextureCubeArray.First2DArrayFace		= m_srvInitParam.firstArraySlice;
			srvDesc.TextureCubeArray.NumCubes				= m_srvInitParam.arraySize;
			srvDesc.TextureCubeArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;
		}
		device->CreateShaderResourceView(m_textureBuffer, &srvDesc, heapHandle);
	}

	const tktkMath::Vector3& TextureBufferData::getTextureSize() const
	{
		return m_textureSize;
	}
}
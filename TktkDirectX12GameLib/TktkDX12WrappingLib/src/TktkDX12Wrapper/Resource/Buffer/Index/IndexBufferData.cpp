#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	IndexBufferData::IndexBufferData(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = (UINT64)sizeof(unsigned short) * (UINT64)indexDataArray.size();
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_indexBuffer)
		);

		unsigned short* mappedIndex{ nullptr };
		m_indexBuffer->Map(0, nullptr, (void**)&mappedIndex);
		std::copy(std::begin(indexDataArray), std::end(indexDataArray), mappedIndex);
		m_indexBuffer->Unmap(0, nullptr);

		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		m_indexBufferView.SizeInBytes = sizeof(unsigned short) * indexDataArray.size();
	}

	IndexBufferData::~IndexBufferData()
	{
		if (m_indexBuffer != nullptr)
		{
			m_indexBuffer->Release();
		}
	}
	void IndexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetIndexBuffer(&m_indexBufferView);
	}

	void IndexBufferData::updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		ID3D12Resource* uploadBuff;

		// CPU�A�N�Z�X�ɓ��������q�[�v�����iCPU����f�[�^���R�s�[���鎞�Ɏg�p����j
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
			resDesc.Width = m_indexBuffer->GetDesc().Width;
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
				IID_PPV_ARGS(&uploadBuff)
			);
		}

		// �C���f�b�N�X�o�b�t�@��CPU�A�N�Z�X�����q�[�v�ɃR�s�[����
		{
			unsigned short* mappedIndex{ nullptr };
			uploadBuff->Map(0, nullptr, (void**)&mappedIndex);
			std::copy(std::begin(indexDataArray), std::end(indexDataArray), mappedIndex);
			uploadBuff->Unmap(0, nullptr);
		}

		// �C���f�b�N�X�o�b�t�@�[�̃o���A���u�ǂݎ��v��Ԃ���u�R�s�[��v��ԂɕύX����
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_indexBuffer;
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
		commandList->ResourceBarrier(1, &barrierDesc);

		if (uploadBuff == nullptr)
		{
#ifdef _DEBUG
			throw std::runtime_error("uploadBuff create error");
			return;
#else
			return;
#endif // _DEBUG

		}

		// GPU�Ԃ̃������̃R�s�[���s��
		commandList->CopyBufferRegion(m_indexBuffer, 0, uploadBuff, 0, static_cast<unsigned long long>(sizeof(unsigned short)) * indexDataArray.size());

		// �C���f�b�N�X�o�b�t�@�[�̃o���A���u�R�s�[��v��Ԃ���u�ǂݎ��v��ԂɕύX����
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);

		// �ꎞ�I�ɃA�b�v���[�h�o�b�t�@��ۑ�����
		m_uploadBufferList.push_front(uploadBuff);
	}

	void IndexBufferData::deleteUploadBufferAll()
	{
		for (auto node : m_uploadBufferList)
		{
			if (node != nullptr)
			{
				node->Release();
			}
		}
		m_uploadBufferList.clear();
	}
}
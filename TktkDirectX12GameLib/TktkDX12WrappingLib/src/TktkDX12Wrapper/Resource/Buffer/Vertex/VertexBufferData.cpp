#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	VertexBufferData::VertexBufferData(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = static_cast<UINT64>(vertexTypeSize) * vertexDataCount;
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
			IID_PPV_ARGS(&m_vertexBuffer)
		);

		{
			void* mappedVertexData{ nullptr };
			m_vertexBuffer->Map(0, nullptr, &mappedVertexData);
			memcpy(mappedVertexData, vertexDataTopPos, vertexTypeSize * vertexDataCount);
			m_vertexBuffer->Unmap(0, nullptr);
		}

		m_vertexBufferView.BufferLocation	= m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes		= vertexTypeSize * vertexDataCount;
		m_vertexBufferView.StrideInBytes	= vertexTypeSize;
	}

	VertexBufferData::~VertexBufferData()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
		}
	}

	void VertexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	}

	void VertexBufferData::updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
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
			resDesc.Width = m_vertexBuffer->GetDesc().Width;
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

		// ���_�o�b�t�@��CPU�A�N�Z�X�����q�[�v�ɃR�s�[����
		{
			void* mappedVertexData{ nullptr };
			uploadBuff->Map(0, nullptr, &mappedVertexData);
			memcpy(mappedVertexData, vertexDataTopPos, vertexTypeSize * vertexDataCount);
			uploadBuff->Unmap(0, nullptr);
		}

		// ���_�o�b�t�@�[�̃o���A���u�ǂݎ��v��Ԃ���u�R�s�[��v��ԂɕύX����
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_vertexBuffer;
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
		commandList->CopyBufferRegion(m_vertexBuffer, 0, uploadBuff, 0, static_cast<unsigned long long>(vertexTypeSize) * vertexDataCount);

		// �萔�o�b�t�@�[�̃o���A���u�R�s�[��v��Ԃ���u�ǂݎ��v��ԂɕύX����
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);

		// �ꎞ�I�ɃA�b�v���[�h�o�b�t�@��ۑ�����
		m_uploadBufferList.push_front(uploadBuff);
	}

	void VertexBufferData::deleteUploadBufferAll()
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
#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/DepthStencilBuffer/DepthStencilBuffer.h"

namespace tktk
{
	DepthStencilBuffer::DepthStencilBuffer(unsigned int depthStencilBufferNum)
		: m_depthStencilBufferDataArray(depthStencilBufferNum)
	{
	}

	void DepthStencilBuffer::create(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		m_depthStencilBufferDataArray.emplaceAt(id, device, initParam);
	}

	void DepthStencilBuffer::use(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_depthStencilBufferDataArray.at(id)->use(commandList);
	}

	void DepthStencilBuffer::unUse(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_depthStencilBufferDataArray.at(id)->unUse(commandList);
	}

	void DepthStencilBuffer::allUse(ID3D12GraphicsCommandList* commandList)
	{
		for (unsigned int i = 0; i < m_depthStencilBufferDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_depthStencilBufferDataArray.at(i);

			if (ptr != nullptr) ptr->use(commandList);
		}
	}

	void DepthStencilBuffer::allUnUse(ID3D12GraphicsCommandList* commandList)
	{
		for (unsigned int i = 0; i < m_depthStencilBufferDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_depthStencilBufferDataArray.at(i);

			if (ptr != nullptr) ptr->unUse(commandList);
		}
	}

	void DepthStencilBuffer::createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_depthStencilBufferDataArray.at(id)->createDepthStencilView(device, heapHandle);
	}

	void DepthStencilBuffer::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_depthStencilBufferDataArray.at(id)->createShaderResourceView(device, heapHandle);
	}

	const tktkMath::Vector2& DepthStencilBuffer::getDepthStencilSize(unsigned int id) const
	{
		return m_depthStencilBufferDataArray.at(id)->getDepthStencilSize();
	}
}
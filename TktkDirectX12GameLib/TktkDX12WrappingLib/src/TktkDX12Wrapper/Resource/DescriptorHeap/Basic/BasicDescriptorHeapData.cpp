#include "TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeapData.h"

namespace tktk
{
	BasicDescriptorHeapData::BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// �f�B�X�N���v�^�e�[�u���̐����̃��������m�ۂ���
		m_descriptorTableSizeArray.reserve(initParam.descriptorTableParamArray.size());

		// �f�B�X�N���v�^�q�[�v�����
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Flags = (initParam.shaderVisible) ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask = 0U;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.NumDescriptors = 0U; /* �l�̏������̂� */

		// �f�B�X�N���v�^�e�[�u���̐��������[�v����
		for (const auto& node : initParam.descriptorTableParamArray)
		{
			// �f�B�X�N���v�^�̐����f�B�X�N���v�^�e�[�u�����Ǘ����Ă��鐔�����Z����
			descHeapDesc.NumDescriptors += node.descriptorParamArray.size();

			// �f�B�X�N���v�^�e�[�u�����̃f�B�X�N���v�^�̐����L�^����
			m_descriptorTableSizeArray.push_back(node.descriptorParamArray.size());
		}
		device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap));
	}

	BasicDescriptorHeapData::~BasicDescriptorHeapData()
	{
		if (m_descriptorHeap != nullptr)
		{
			m_descriptorHeap->Release();
		}
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BasicDescriptorHeapData::getCpuHeapHandleArray(ID3D12Device* device) const
	{
		// �f�B�X�N���v�^�q�[�v��ɑ��݂���f�B�X�N���v�^�̐����̃��������m�ۂ���
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		unsigned int descriptorNum = m_descriptorHeap->GetDesc().NumDescriptors;
		handleArray.reserve(descriptorNum);

		// ���g�̐擪�̃A�h���X���擾
		auto cpuHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

		for (unsigned int i = 0; i < descriptorNum; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}
		return handleArray;
	}

	ID3D12DescriptorHeap* BasicDescriptorHeapData::getPtr() const
	{
		return m_descriptorHeap;
	}

	void BasicDescriptorHeapData::setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		auto gpuHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		
		for (unsigned int i = 0; i < m_descriptorTableSizeArray.size(); i++)
		{
			commandList->SetGraphicsRootDescriptorTable(i, gpuHandle);
			gpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * static_cast<unsigned long long>(m_descriptorTableSizeArray.at(i));
		}
	}
}
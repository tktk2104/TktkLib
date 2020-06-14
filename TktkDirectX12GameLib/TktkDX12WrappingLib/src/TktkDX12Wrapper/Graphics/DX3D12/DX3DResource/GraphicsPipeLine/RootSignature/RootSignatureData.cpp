#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/RootSignature/RootSignatureData.h"

namespace tktk
{
	RootSignatureData::RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		// ���[�g�p�����[�^�[�̐��������������m�ۂ���
		std::vector<D3D12_ROOT_PARAMETER> rootParamArray;
		rootParamArray.reserve(initParam.rootParamArray.size());

		// �f�B�X�N���v�^�[�����W�̒l��������z������[�g�p�����[�^�[�̐������m�ۂ���
		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> descriptorTableArray;
		descriptorTableArray.resize(initParam.rootParamArray.size());

		// ���[�g�p�����[�^�[�̐��������[�v����
		for (unsigned int i = 0; i < initParam.rootParamArray.size(); i++)
		{
			// ���⏕�ϐ�
			const auto& rootParamInitParam	= initParam.rootParamArray.at(i);
			auto&		descriptorTable		= descriptorTableArray.at(i);

			// ���̃��[�g�p�����[�^�[�������Ă���f�B�X�N���v�^�����W�̐��������������m�ۂ���
			descriptorTable.reserve(rootParamInitParam.descriptorTable.size());

			// �f�B�X�N���v�^�����W�̐��������[�v����
			for (unsigned int j = 0; j < rootParamInitParam.descriptorTable.size(); j++)
			{
				// ���⏕�ϐ�
				const auto& descriptorRangeInitParam = rootParamInitParam.descriptorTable.at(j);

				// �f�B�X�N���v�^�����W�̐ݒ������
				D3D12_DESCRIPTOR_RANGE descriptorRange{};
				descriptorRange.NumDescriptors						= descriptorRangeInitParam.numDescriptors;
				descriptorRange.RangeType							= descriptorRangeInitParam.type;
				descriptorRange.BaseShaderRegister					= descriptorRangeInitParam.startRegisterNum + j;
				descriptorRange.OffsetInDescriptorsFromTableStart	= D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

				descriptorTable.push_back(descriptorRange);
			}

			// ���[�g�p�����[�^�̐ݒ������
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ShaderVisibility						= rootParamInitParam.shaderVisibility;
			rootParam.ParameterType							= D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.DescriptorTable.pDescriptorRanges		= descriptorTable.data();
			rootParam.DescriptorTable.NumDescriptorRanges	= descriptorTable.size();

			rootParamArray.push_back(rootParam);
		}

		// �T���v���[�f�X�N�̐��������������m�ۂ���
		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescArray;
		samplerDescArray.reserve(initParam.samplerDescArray.size());

		// �T���v���[�f�X�N�̐��������[�v����
		for (const auto& node : initParam.samplerDescArray)
		{
			// �T���v���[�f�X�N�̐ݒ������
			D3D12_STATIC_SAMPLER_DESC samplerDesc{};
			samplerDesc.AddressU			= node.addressU;
			samplerDesc.AddressV			= node.addressV;
			samplerDesc.AddressW			= node.addressW;
			samplerDesc.BorderColor			= node.bordercolor;
			samplerDesc.Filter				= node.filter;
			samplerDesc.MaxLOD				= node.maxLod;
			samplerDesc.MinLOD				= node.minLod;
			samplerDesc.ShaderVisibility	= node.shaderVisibility;
			samplerDesc.ComparisonFunc		= node.comparisonFunc;
			samplerDesc.ShaderRegister		= node.shaderRegister;

			samplerDescArray.push_back(samplerDesc);
		}

		// ���[�g�V�O�l�`���̐ݒ������
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags				= initParam.flag;
		rootSignatureDesc.pParameters		= rootParamArray.data();
		rootSignatureDesc.NumParameters		= rootParamArray.size();
		rootSignatureDesc.pStaticSamplers	= samplerDescArray.data();
		rootSignatureDesc.NumStaticSamplers = samplerDescArray.size();

		// ���[�g�V�O�l�`�������
		ID3DBlob* rootSigBlob{ nullptr };
		ID3DBlob* errorBlob{ nullptr };
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
		rootSigBlob->Release();
	}

	RootSignatureData::~RootSignatureData()
	{
		if (m_rootSignature != nullptr)
		{
			m_rootSignature->Release();
		}
	}

	ID3D12RootSignature* RootSignatureData::getPtr() const
	{
		return m_rootSignature;
	}

	void RootSignatureData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->SetGraphicsRootSignature(m_rootSignature);
	}
}
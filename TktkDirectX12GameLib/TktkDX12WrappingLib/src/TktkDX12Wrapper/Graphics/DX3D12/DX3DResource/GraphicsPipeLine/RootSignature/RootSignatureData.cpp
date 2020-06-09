#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/RootSignature/RootSignatureData.h"

namespace tktk
{
	RootSignatureData::RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		std::vector<D3D12_ROOT_PARAMETER> rootParamArray;
		rootParamArray.reserve(initParam.rootParamArray.size());

		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> descriptorRangeArray;
		descriptorRangeArray.resize(initParam.rootParamArray.size());

		for (unsigned int i = 0; i < initParam.rootParamArray.size(); i++)
		{
			descriptorRangeArray.at(i).reserve(initParam.rootParamArray.at(i).descriptorTable.size());

			const auto& descriptorTable = initParam.rootParamArray.at(i).descriptorTable;
			for (unsigned int j = 0; j < descriptorTable.size(); j++)
			{
				D3D12_DESCRIPTOR_RANGE descriptorRange{};
				descriptorRange.NumDescriptors = descriptorTable.at(j).numDescriptors;
				descriptorRange.RangeType = descriptorTable.at(j).type;
				descriptorRange.BaseShaderRegister = descriptorTable.at(j).startRegisterNum + j;
				descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

				descriptorRangeArray.at(i).push_back(descriptorRange);
			}

			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ShaderVisibility = initParam.rootParamArray.at(i).shaderVisibility;
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.DescriptorTable.pDescriptorRanges = descriptorRangeArray.at(i).data();
			rootParam.DescriptorTable.NumDescriptorRanges = descriptorRangeArray.at(i).size();

			rootParamArray.push_back(rootParam);
		}

		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescArray;
		samplerDescArray.reserve(initParam.samplerDescArray.size());
		for (const auto& node : initParam.samplerDescArray)
		{
			D3D12_STATIC_SAMPLER_DESC samplerDesc{};
			samplerDesc.AddressU = node.addressU;
			samplerDesc.AddressV = node.addressV;
			samplerDesc.AddressW = node.addressW;
			samplerDesc.BorderColor = node.bordercolor;
			samplerDesc.Filter = node.filter;
			samplerDesc.MaxLOD = node.maxLod;
			samplerDesc.MinLOD = node.minLod;
			samplerDesc.ShaderVisibility = node.shaderVisibility;
			samplerDesc.ComparisonFunc = node.comparisonFunc;
			samplerDescArray.push_back(samplerDesc);
		}

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = initParam.flag;
		rootSignatureDesc.pParameters = rootParamArray.data();
		rootSignatureDesc.NumParameters = rootParamArray.size();
		rootSignatureDesc.pStaticSamplers = samplerDescArray.data();
		rootSignatureDesc.NumStaticSamplers = samplerDescArray.size();

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
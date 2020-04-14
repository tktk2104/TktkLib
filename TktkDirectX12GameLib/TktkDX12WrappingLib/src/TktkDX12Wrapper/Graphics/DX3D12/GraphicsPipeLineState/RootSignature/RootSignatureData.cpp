#include "TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/RootSignature/RootSignatureData.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	RootSignatureData::~RootSignatureData()
	{
		if (m_rootSignature != nullptr)
		{
			m_rootSignature->Release();
		}
	}

	void RootSignatureData::initialize(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		if (m_rootSignature != nullptr)
		{
			m_rootSignature->Release();
		}
		std::vector<D3D12_ROOT_PARAMETER> rootParamArray;
		rootParamArray.reserve(initParam.m_rootParamArray.size());

		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> descriptorRangeArray;
		descriptorRangeArray.resize(initParam.m_rootParamArray.size());

		for (unsigned int i = 0; i < initParam.m_rootParamArray.size(); i++)
		{
			descriptorRangeArray.at(i).reserve(initParam.m_rootParamArray.at(i).m_descriptorTableArray.size());

			for (const auto& descriptorTableInitParam : initParam.m_rootParamArray.at(i).m_descriptorTableArray)
			{
				D3D12_DESCRIPTOR_RANGE descriptorRange{};
				descriptorRange.NumDescriptors = descriptorTableInitParam.m_numDescriptors;
				descriptorRange.RangeType = descriptorTableInitParam.m_type;
				descriptorRange.BaseShaderRegister = 0;
				descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

				descriptorRangeArray.at(i).push_back(descriptorRange);
			}

			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ShaderVisibility = initParam.m_rootParamArray.at(i).m_shaderVisibility;
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.DescriptorTable.pDescriptorRanges = descriptorRangeArray.at(i).data();
			rootParam.DescriptorTable.NumDescriptorRanges = descriptorRangeArray.at(i).size();

			rootParamArray.push_back(rootParam);
		}

		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescArray;
		samplerDescArray.reserve(initParam.m_samplerDescArray.size());
		for (const auto& node : initParam.m_samplerDescArray)
		{
			D3D12_STATIC_SAMPLER_DESC samplerDesc{};
			samplerDesc.AddressU = node.m_addressU;
			samplerDesc.AddressV = node.m_addressV;
			samplerDesc.AddressW = node.m_addressW;
			samplerDesc.BorderColor = node.m_bordercolor;
			samplerDesc.Filter = node.m_filter;
			samplerDesc.MaxLOD = node.m_maxLod;
			samplerDesc.MinLOD = node.m_minLod;
			samplerDesc.ShaderVisibility = node.m_shaderVisibility;
			samplerDesc.ComparisonFunc = node.m_comparisonFunc;
			samplerDescArray.push_back(samplerDesc);
		}

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = initParam.m_flag;
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

	ID3D12RootSignature* RootSignatureData::getPtr() const
	{
#ifdef _DEBUG
		if (m_rootSignature == nullptr)
		{
			throw std::runtime_error("Not Create RootSignature");
		}
#endif // _DEBUG
		return m_rootSignature;
	}

	void RootSignatureData::set(ID3D12GraphicsCommandList* commandList) const
	{
#ifdef _DEBUG
		if (m_rootSignature == nullptr)
		{
			throw std::runtime_error("Not Create RootSignature");
		}
#endif // _DEBUG
		commandList->SetGraphicsRootSignature(m_rootSignature);
	}
}
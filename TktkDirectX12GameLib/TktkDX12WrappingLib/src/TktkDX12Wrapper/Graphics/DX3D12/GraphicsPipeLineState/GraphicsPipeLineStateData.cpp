#include "TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateData.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	GraphicsPipeLineStateData::~GraphicsPipeLineStateData()
	{
		if (m_pipeLineState != nullptr)
		{
			m_pipeLineState->Release();
		}
	}

	void GraphicsPipeLineStateData::initialize(
		ID3D12Device* device,
		const GraphicsPipeLineStateInitParam& initParam,
		const std::vector<char>& vsByteArray,
		const std::vector<char>& psByteArray,
		ID3D12RootSignature* rootSignaturePtr,
		int rootSignatureIndex)
	{
		if (m_pipeLineState != nullptr)
		{
			m_pipeLineState->Release();
		}

		m_rootSignatureIndex = rootSignatureIndex;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipeLineStateDesc{};
		graphicsPipeLineStateDesc.pRootSignature					= rootSignaturePtr;
		graphicsPipeLineStateDesc.VS.pShaderBytecode				= vsByteArray.data();
		graphicsPipeLineStateDesc.VS.BytecodeLength					= vsByteArray.size();
		graphicsPipeLineStateDesc.PS.pShaderBytecode				= psByteArray.data();
		graphicsPipeLineStateDesc.PS.BytecodeLength					= psByteArray.size();
		graphicsPipeLineStateDesc.SampleMask						= D3D12_DEFAULT_SAMPLE_MASK;
		graphicsPipeLineStateDesc.RasterizerState					= initParam.m_rasterizerDesc;
		graphicsPipeLineStateDesc.BlendState						= initParam.m_blendDesc;
		graphicsPipeLineStateDesc.InputLayout.pInputElementDescs	= initParam.m_inputLayoutArray.data();
		graphicsPipeLineStateDesc.InputLayout.NumElements			= initParam.m_inputLayoutArray.size();
		graphicsPipeLineStateDesc.IBStripCutValue					= D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		graphicsPipeLineStateDesc.PrimitiveTopologyType				= initParam.m_primitiveTopology;
		graphicsPipeLineStateDesc.NumRenderTargets					= initParam.m_renderTargetFormatArray.size();
		for (unsigned int i = 0; i < graphicsPipeLineStateDesc.NumRenderTargets; i++)
		{
			graphicsPipeLineStateDesc.RTVFormats[i] = initParam.m_renderTargetFormatArray.at(i);
		}
		graphicsPipeLineStateDesc.SampleDesc.Count = 1;
		graphicsPipeLineStateDesc.SampleDesc.Quality = 0;

		device->CreateGraphicsPipelineState(&graphicsPipeLineStateDesc, IID_PPV_ARGS(&m_pipeLineState));
	}

	int GraphicsPipeLineStateData::getUseRootSignatureIndex() const
	{
#ifdef _DEBUG
		if (m_pipeLineState == nullptr)
		{
			throw std::runtime_error("Not Create RootSignature");
		}
#endif // _DEBUG
		return m_rootSignatureIndex;
	}

	void GraphicsPipeLineStateData::set(ID3D12GraphicsCommandList* commandList) const
	{
#ifdef _DEBUG
		if (m_pipeLineState == nullptr)
		{
			throw std::runtime_error("Not Create RootSignature");
		}
#endif // _DEBUG
		commandList->SetPipelineState(m_pipeLineState);
	}
}
#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateData.h"

namespace tktk
{
	PipeLineStateData::PipeLineStateData(
		ID3D12Device* device,
		const PipeLineStateInitParam& initParam,
		const std::vector<char>& vsByteArray,
		const std::vector<char>& psByteArray,
		ID3D12RootSignature* rootSignaturePtr
	)
	{
		m_rootSignatureId = initParam.rootSignatureId;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipeLineStateDesc{};
		graphicsPipeLineStateDesc.pRootSignature = rootSignaturePtr;
		graphicsPipeLineStateDesc.VS.pShaderBytecode = vsByteArray.data();
		graphicsPipeLineStateDesc.VS.BytecodeLength = vsByteArray.size();
		graphicsPipeLineStateDesc.PS.pShaderBytecode = psByteArray.data();
		graphicsPipeLineStateDesc.PS.BytecodeLength = psByteArray.size();
		graphicsPipeLineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		graphicsPipeLineStateDesc.RasterizerState = initParam.rasterizerDesc;
		graphicsPipeLineStateDesc.BlendState = initParam.blendDesc;
		graphicsPipeLineStateDesc.InputLayout.pInputElementDescs = initParam.inputLayoutArray.data();
		graphicsPipeLineStateDesc.InputLayout.NumElements = initParam.inputLayoutArray.size();
		graphicsPipeLineStateDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		graphicsPipeLineStateDesc.PrimitiveTopologyType = initParam.primitiveTopology;
		graphicsPipeLineStateDesc.NumRenderTargets = initParam.renderTargetFormatArray.size();
		for (unsigned int i = 0; i < graphicsPipeLineStateDesc.NumRenderTargets; i++)
		{
			graphicsPipeLineStateDesc.RTVFormats[i] = initParam.renderTargetFormatArray.at(i);
		}
		graphicsPipeLineStateDesc.SampleDesc.Count = 1;
		graphicsPipeLineStateDesc.SampleDesc.Quality = 0;

		graphicsPipeLineStateDesc.DepthStencilState.DepthEnable = initParam.useDepth;

		if (initParam.useDepth)
		{
			graphicsPipeLineStateDesc.DepthStencilState.DepthWriteMask = (initParam.writeDepth) ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
			graphicsPipeLineStateDesc.DepthStencilState.DepthFunc = initParam.depthFunc;
			graphicsPipeLineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		}

		device->CreateGraphicsPipelineState(&graphicsPipeLineStateDesc, IID_PPV_ARGS(&m_pipeLineState));
	}

	PipeLineStateData::~PipeLineStateData()
	{
		if (m_pipeLineState != nullptr)
		{
			m_pipeLineState->Release();
		}
	}

	unsigned int PipeLineStateData::getUseRootSignatureIndex() const
	{
		return m_rootSignatureId;
	}

	void PipeLineStateData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->SetPipelineState(m_pipeLineState);
	}
}
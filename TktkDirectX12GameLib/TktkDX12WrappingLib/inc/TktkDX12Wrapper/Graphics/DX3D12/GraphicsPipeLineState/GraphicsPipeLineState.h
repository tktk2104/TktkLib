#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <string>
#include <vector>
#include "GraphicsPipeLineStateData.h"
#include "RootSignature/RootSignature.h"

namespace tktk
{
	class GraphicsPipeLineState
	{
	public:

		GraphicsPipeLineState(unsigned int graphicsPipeLineNum, unsigned int rootSignatureNum);

	public:

		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		void createGraphicsPipeLineState(unsigned int graphicsPipeLineId, ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		RootSignature m_rootSignature;

		std::vector<GraphicsPipeLineStateData> m_graphicsPipeLineStateDataArray{};
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_
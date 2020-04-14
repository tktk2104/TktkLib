#ifndef GRAPHICS_PIPELINE_STATE_DATA_H_
#define GRAPHICS_PIPELINE_STATE_DATA_H_

#include <d3d12.h>
#include "GraphicsPipeLineStateInitParam.h"

namespace tktk
{
	class GraphicsPipeLineStateData
	{
	public:

		GraphicsPipeLineStateData() = default;
		~GraphicsPipeLineStateData();

	public:

		void initialize(
			ID3D12Device* device,
			const GraphicsPipeLineStateInitParam& initParam,
			const std::vector<char>& vsByteArray,
			const std::vector<char>& psByteArray,
			ID3D12RootSignature* rootSignaturePtr,
			int rootSignatureIndex
		);

		int getUseRootSignatureIndex() const;

		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		int						m_rootSignatureIndex{};
		ID3D12PipelineState*	m_pipeLineState{ nullptr };
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_DATA_H_
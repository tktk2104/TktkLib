#ifndef PIPELINE_STATE_DATA_H_
#define PIPELINE_STATE_DATA_H_

#include <d3d12.h>
#include "PipeLineStateInitParam.h"

namespace tktk
{
	class PipeLineStateData
	{
	public:

		PipeLineStateData(
			ID3D12Device* device,
			const PipeLineStateInitParam& initParam,
			const std::vector<char>& vsByteArray,
			const std::vector<char>& psByteArray,
			ID3D12RootSignature* rootSignaturePtr
		);
		~PipeLineStateData();

	public:

		unsigned int getUseRootSignatureIndex() const;

		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		int						m_rootSignatureId{};
		ID3D12PipelineState*	m_pipeLineState{ nullptr };
	};
}
#endif // !PIPELINE_STATE_DATA_H_
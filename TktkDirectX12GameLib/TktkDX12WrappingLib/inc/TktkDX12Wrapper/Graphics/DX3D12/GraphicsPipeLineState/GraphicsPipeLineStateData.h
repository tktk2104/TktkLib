#ifndef GRAPHICS_PIPELINE_STATE_DATA_H_
#define GRAPHICS_PIPELINE_STATE_DATA_H_

#include <d3d12.h>

namespace tktk
{
	class GraphicsPipeLineStateData
	{
	public:

		GraphicsPipeLineStateData() = default;
		~GraphicsPipeLineStateData();

	public:

		void initialize(ID3D12Device* device);

	private:

		ID3D12PipelineState* m_pipeLineState{ nullptr };
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_DATA_H_
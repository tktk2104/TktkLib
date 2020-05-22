#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <string>
#include <vector>
#include "PipeLineStateData.h"

namespace tktk
{
	class PipeLineState
	{
	public:

		PipeLineState(unsigned int pipeLineNum);

	public:

		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		int getUseRootSignatureIndex(unsigned int id) const;

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<PipeLineStateData> m_pipeLineStateDataArray{};
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_
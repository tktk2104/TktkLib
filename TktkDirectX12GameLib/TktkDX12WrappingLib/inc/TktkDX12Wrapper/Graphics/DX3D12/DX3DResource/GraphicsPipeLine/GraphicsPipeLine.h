#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include "PipeLineState/PipeLineState.h"
#include "RootSignature/RootSignature.h"

namespace tktk
{
	class GraphicsPipeLine
	{
	public:

		GraphicsPipeLine(unsigned int pipeLineNum, unsigned int rootSignatureNum);

	public:

		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

	public:

		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

	public:

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		RootSignature m_rootSignature;
		PipeLineState m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_

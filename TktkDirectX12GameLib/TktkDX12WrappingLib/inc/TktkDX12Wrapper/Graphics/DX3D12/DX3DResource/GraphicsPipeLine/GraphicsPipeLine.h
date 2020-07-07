#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include "PipeLineState/PipeLineState.h"
#include "RootSignature/RootSignature.h"

namespace tktk
{
	// �O���t�B�b�N�p�C�v���C�����Ǘ�����N���X
	class GraphicsPipeLine
	{
	public:

		GraphicsPipeLine(unsigned int pipeLineNum, unsigned int rootSignatureNum);

	public:

		// ���[�g�V�O�l�`�������
		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

	public:

		// �p�C�v���C���X�e�[�g�����
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

	public:

		// �O���t�B�b�N�p�C�v���C�����R�}���h���X�g�ɓo�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		RootSignature m_rootSignature;
		PipeLineState m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_

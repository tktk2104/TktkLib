#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "PipeLineStateData.h"

namespace tktk
{
	// �uPipeLineStateData�v���Ǘ�����N���X
	class PipeLineState
	{
	public:

		PipeLineState(unsigned int pipeLineNum);
		~PipeLineState() = default;

	public:

		// �uPipeLineStateData�v�̃C���X�^���X�����
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// �w�肵���p�C�v���C���X�e�[�g���g�p���Ă��郋�[�g�V�O�l�`����ID���擾����
		unsigned int getUseRootSignatureIndex(unsigned int id) const;

		// �w�肵���p�C�v���C���X�e�[�g���R�}���h���X�g�ɓo�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_
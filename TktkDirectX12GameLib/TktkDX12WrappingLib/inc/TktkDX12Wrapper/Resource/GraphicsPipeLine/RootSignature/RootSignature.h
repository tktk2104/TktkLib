#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RootSignatureData.h"

namespace tktk
{
	// �uRootSignatureData�v���Ǘ�����N���X
	class RootSignature
	{
	public:

		RootSignature(unsigned int rootSignatureNum);
		~RootSignature() = default;

	public:

		// �uRootSignatureData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		// �w�肵�����[�g�V�O�l�`���̃|�C���^���擾����
		ID3D12RootSignature* getPtr(unsigned int id) const;

		// �w�肵�����[�g�V�O�l�`�����R�}���h���X�g�ɓo�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<RootSignatureData> m_rootSignatureDataArray;
	};
}
#endif // !ROOT_SIGNATURE_H_
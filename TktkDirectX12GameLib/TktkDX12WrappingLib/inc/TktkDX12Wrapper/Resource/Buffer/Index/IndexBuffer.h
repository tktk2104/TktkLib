#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "IndexBufferData.h"

namespace tktk
{
	// �uIndexBufferData�v���Ǘ�����N���X
	class IndexBuffer
	{
	public:

		IndexBuffer(unsigned int indexBufferNum);
		~IndexBuffer() = default;

	public:

		// �uIndexBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �C���f�b�N�X�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		HeapArray<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_
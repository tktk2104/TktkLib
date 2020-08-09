#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "VertexBufferData.h"

namespace tktk
{
	// �uVertexBufferData�v���Ǘ�����N���X
	class VertexBuffer
	{
	public:

		VertexBuffer(unsigned int vertexBufferNum);
		~VertexBuffer() = default;

	public:

		// �uVertexBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		HeapArray<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_
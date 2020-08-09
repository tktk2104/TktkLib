#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <d3d12.h>
#include <forward_list>

namespace tktk
{
	// ���_�o�b�t�@���Ǘ�����N���X
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		~VertexBufferData();

	public:

		// �R�}���h���X�g�ɒ��_�o�b�t�@��o�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

		// ���_�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		ID3D12Resource*				m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView	{};
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_
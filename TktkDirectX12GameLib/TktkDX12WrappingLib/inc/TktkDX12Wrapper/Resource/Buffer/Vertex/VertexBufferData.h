#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <vector>
#include <d3d12.h>

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

	private:

		ID3D12Resource*				m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView	{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_
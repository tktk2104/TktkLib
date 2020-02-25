#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <d3d11.h>
#include "../_MeshInitParams/VertexBufferInitParams.h"

namespace tktk
{
	class VertexBuffer
	{
	public:

		// �Ӑ}�I�Ɂgexplicit�h���O���Ă���
		VertexBuffer(const VertexBufferInitParams& params);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator = (const VertexBuffer& other) = delete;

	public:

		// ���_�o�b�t�@�̃|�C���^���擾����
		ID3D11Buffer* getVertexBufferPtr() const;

		// �X�g���C�h���擾����
		unsigned int getStride() const;

		// �I�t�Z�b�g���擾����
		unsigned int getOffset() const;


	private:

		// ���_�o�b�t�@�̃|�C���^
		ID3D11Buffer* m_vertexBufferPtr{ nullptr };

		// �X�g���C�h
		unsigned int m_stride = 0U;

		// �I�t�Z�b�g
		unsigned int m_offset = 0U;
	};
}
#endif // !VERTEX_BUFFER_H_

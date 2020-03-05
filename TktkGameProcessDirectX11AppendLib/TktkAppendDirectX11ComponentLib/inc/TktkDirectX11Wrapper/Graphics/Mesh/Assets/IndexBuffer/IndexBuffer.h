#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <vector>
#include <d3d11.h>
#include "../_MeshInitParams/IndexBufferInitParams.h"

namespace tktk
{
	class IndexBuffer
	{
	public:

		// �Ӑ}�I�Ɂgexplicit�h���O���Ă���
		IndexBuffer(const IndexBufferInitParams& params);
		~IndexBuffer();

		// �R�s�[�֎~
		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer& operator = (const IndexBuffer& other) = delete;

	public:

		// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ肷��
		void setBuffer() const;

	private:

		// �C���f�b�N�X�o�b�t�@�̃|�C���^
		ID3D11Buffer* m_bufferPtr{ nullptr };
	};
}
#endif // !INDEX_BUFFER_H_

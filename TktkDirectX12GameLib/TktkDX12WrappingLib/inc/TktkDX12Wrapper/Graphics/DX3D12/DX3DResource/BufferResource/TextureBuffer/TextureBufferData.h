#ifndef TEXTURE_BUFFER_DATA_H_
#define TEXTURE_BUFFER_DATA_H_

#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector3.h>
#include "TextureBufferInitParam.h"
#include "ShaderResourceViewInitParam.h"

namespace tktk
{
	// �e�N�X�`���o�b�t�@���Ǘ�����N���X
	class TextureBufferData
	{
	public:

		// �R�}���h���X�g���g�킸�ɍ��R���X�g���N�^
		TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���č��R���X�g���N�^
		TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		~TextureBufferData();

	public:

		// �����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx() const;

	private:

		tktkMath::Vector3			m_textureSize{ 1.0f, 1.0f, 1.0f };
		ShaderResourceViewInitParam	m_srvInitParam{};
		ID3D12Resource*				m_textureBuffer{ nullptr };
		ID3D12Resource*				m_uploadBuff{ nullptr };
	};
}
#endif // !TEXTURE_BUFFER_DATA_H_
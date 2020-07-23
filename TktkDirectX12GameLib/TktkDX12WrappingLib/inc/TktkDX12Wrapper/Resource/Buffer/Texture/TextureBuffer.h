#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "TextureBufferData.h"

namespace tktk
{
	// �uTextureBufferData�v���Ǘ�����N���X
	class TextureBuffer
	{
	public:

		TextureBuffer(unsigned int textureBufferNum);
		~TextureBuffer() = default;

	public:
		
		// �R�}���h���X�g���g�킸�ɁuTextureBufferData�v�̃C���X�^���X�����
		void cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����
		void gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�ɁuTextureBufferData�v�̃C���X�^���X�����
		void cpuPriorityLoad(unsigned int id, ID3D12Device* device, const std::string& texDataPath);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����
		void gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);
	
		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
		
		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(unsigned int id) const;

	private:

		HeapArray<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_
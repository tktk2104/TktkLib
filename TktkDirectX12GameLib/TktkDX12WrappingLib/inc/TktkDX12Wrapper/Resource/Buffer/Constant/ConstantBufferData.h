#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <d3d12.h>
#include <forward_list>

namespace tktk
{
	// �萔�o�b�t�@���Ǘ�����N���X
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		~ConstantBufferData();

	public:

		// �����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �萔�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		ID3D12Resource* m_constantBuffer{ nullptr };
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_
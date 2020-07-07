#ifndef RENDER_TARGET_BUFFER_DATA_H_
#define RENDER_TARGET_BUFFER_DATA_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �����_�[�^�[�Q�b�g�o�b�t�@���Ǘ�����N���X
	class RenderTargetBufferData
	{
	public:

		// �[������o�b�t�@�����R���X�g���N�^
		RenderTargetBufferData(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�C������o�b�N�o�b�t�@���擾���č��R���X�g���N�^
		RenderTargetBufferData(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);
		~RenderTargetBufferData();

	public:

		// ���g�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList);

		// ���g�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList);

		// ���g�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(ID3D12GraphicsCommandList* commandList);

		// ���g�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(ID3D12GraphicsCommandList* commandList);

		// �����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx() const;

	private:

		tktkMath::Vector2	m_renderTargetSize;
		ID3D12Resource*		m_renderTargetBuffer{ nullptr };
		bool				m_mustRelease{ true };
	};
}
#endif // !RENDER_TARGET_BUFFER_DATA_H_
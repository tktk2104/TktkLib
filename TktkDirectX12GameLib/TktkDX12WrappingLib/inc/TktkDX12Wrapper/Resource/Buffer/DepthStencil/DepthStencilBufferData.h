#ifndef DEPTH_STENCIL_BUFFER_DATA_H_
#define DEPTH_STENCIL_BUFFER_DATA_H_

#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "DepthStencilBufferInitParam.h"

namespace tktk
{
	// �[�x�o�b�t�@���Ǘ�����N���X
	class DepthStencilBufferData
	{
	public:

		DepthStencilBufferData(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);
		~DepthStencilBufferData() = default;

	public:

		// ���g�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWrite(ID3D12GraphicsCommandList* commandList);

		// ���g�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWrite(ID3D12GraphicsCommandList* commandList);

		// �����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�A�G���[��f���܂�
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx() const;

	private:

		bool				m_useAsShaderResource;
		tktkMath::Vector2	m_depthStencilSize;
		ID3D12Resource*		m_depthStencilBuffer{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_BUFFER_DATA_H_
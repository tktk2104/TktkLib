#include "TktkDX12Game/DXGameResource/PostEffect/PostEffectMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectMaterialData::PostEffectMaterialData(const PostEffectMaterialInitParam& initParam)
		: m_usePipeLineStateId(initParam.usePipeLineStateId)
		, m_useDescriptorHeapId(initParam.useDescriptorHeapId)
	{
	}

	void PostEffectMaterialData::drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportId);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectId);

		// �����_�[�^�[�Q�b�g��ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBuffer();
		}
		else
		{
			DX12GameManager::setRenderTarget(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �`��Ŏg�p����p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(m_usePipeLineStateId);

		// �`��Ŏg�p����f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapId} });

		// �g���C�A���O���X�g���b�v�ŕ`�悷��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �|���S���̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Sprite));

		// �|���S���̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemId(SystemIndexBufferType::Sprite));

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRenderTarget(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}
}
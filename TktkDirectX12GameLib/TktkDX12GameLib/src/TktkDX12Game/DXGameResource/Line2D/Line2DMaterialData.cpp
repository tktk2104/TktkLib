#include "TktkDX12Game/DXGameResource/Line2D/Line2DMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DConstantBufferData.h"

namespace tktk
{
	Line2DMaterialData::Line2DMaterialData(const Line2DMaterialDataInitParam& initParam)
		: m_createdVertexBufferId(initParam.createVertexBufferId)
	{
	}

	void Line2DMaterialData::drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// ���g�̒��_�o�b�t�@�����
		DX12GameManager::createVertexBuffer(m_createdVertexBufferId, drawFuncArgs.lineVertexArray);

		// ���C���p�̒萔�o�b�t�@���X�V����
		updateLine2DCbuffer(drawFuncArgs);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportId);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectId);

		// �����_�[�^�[�Q�b�g��ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// ���C���p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Line2D));

		// �u�����h�t�@�N�^�[��ݒ肷��
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// ���g�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::Line2D)} });
		
		// ���C���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// ���g�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_createdVertexBufferId);
		
		// �h���[�R�[��
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}
	}

	// ���C���p�̒萔�o�b�t�@���X�V����
	void Line2DMaterialData::updateLine2DCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const
	{
		Line2DConstantBufferData cbufferData{};
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			cbufferData.worldMatrix[i] = drawFuncArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		cbufferData.lineColor = drawFuncArgs.lineColor;
		cbufferData.screenSize = DX12GameManager::getWindowSize();

		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Line2D), cbufferData);
	}
}
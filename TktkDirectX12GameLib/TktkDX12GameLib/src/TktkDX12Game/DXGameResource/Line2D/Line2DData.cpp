#include "TktkDX12Game/DXGameResource/Line2D/Line2DData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DConstantBufferData.h"

namespace tktk
{
	void Line2DData::drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const
	{
		// ���C���p�̒��_�o�b�t�@�����
		createVertexBuffer(drawFuncArgs.lineVertexArray);

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

		// ���C���p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::Line2D)} });
		
		// ���C���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// ���C���p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Line2D));
		
		// �h���[�R�[��
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}

	// ���C���p�̒��_�o�b�t�@�����
	void Line2DData::createVertexBuffer(const std::vector<tktkMath::Vector2>& lineVertexArray) const
	{
		DX12GameManager::createVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Line2D), lineVertexArray);
	}

	// ���C���p�̒萔�o�b�t�@���X�V����
	void Line2DData::updateLine2DCbuffer(const Line2DDrawFuncArgs& drawFuncArgs) const
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
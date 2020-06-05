#include "TktkDX12Game/DXGameResource/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_createDescriptorHeapId(initParam.createDescriptorHeapId)
		, m_blendRate(initParam.blendRate)
		, m_textureUvOffset(initParam.textureUvOffset)
		, m_textureUvMulRate(initParam.textureUvMulRate)
		, m_textureSize(DX12GameManager::getTextureSize(initParam.useTextureId).x, DX12GameManager::getTextureSize(initParam.useTextureId).y)
		, m_spriteCenterRate(initParam.spriteCenterRate)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.m_shaderVisible = true;
		descriptorHeapInitParam.m_descriptorParamArray.resize(2U);
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).type = BasicDescriptorType::textureBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).id = initParam.useTextureId;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).type = BasicDescriptorType::constantBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).id = DX12GameManager::getSystemId(SystemConstantBufferType::Sprite);

		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void SpriteMaterialData::drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		// �X�v���C�g�p�̒萔�o�b�t�@���X�V����
		updateSpriteConstantBuffer(drawFuncArgs.worldMatrix);

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

		// �X�v���C�g�p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Sprite));

		// �X�v���C�g�p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId} });

		// �g���C�A���O���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �X�v���C�g�p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Sprite));

		// �X�v���C�g�p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
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

	// �X�v���C�g�p�̒萔�o�b�t�@���X�V����
	void SpriteMaterialData::updateSpriteConstantBuffer(const tktkMath::Matrix3& worldMatrix)
	{
		SpriteConstantBufferData constantBufferData;
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			constantBufferData.worldMatrix[i] = worldMatrix.m[i / 4U][i % 4U];
		}
		constantBufferData.blendRate = m_blendRate;
		constantBufferData.textureUvOffset = m_textureUvOffset;
		constantBufferData.textureUvMulRate = m_textureUvMulRate;
		constantBufferData.textureSize = m_textureSize;
		constantBufferData.spriteCenterRate = m_spriteCenterRate;
		constantBufferData.screenSize = DX12GameManager::getWindowSize();

		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::Sprite), constantBufferData);
	}
}
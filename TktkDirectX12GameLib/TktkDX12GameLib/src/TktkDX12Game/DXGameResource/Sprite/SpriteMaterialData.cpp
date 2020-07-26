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
		, m_spriteCenterRate(initParam.spriteCenterRate)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �X�v���C�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ initParam.srvBufferType, initParam.useBufferId }
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �X�v���C�g�萔�o�b�t�@�̂P���
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::Sprite) }
			};
		}

		auto textureBufferSize = tktkMath::vec3Zero;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = DX12GameManager::getTextureBufferSizePx(initParam.useBufferId);
			m_textureSize = { textureBufferSize.x, textureBufferSize.y };
			break;

		case BufferType::renderTarget:

			m_textureSize = DX12GameManager::getRtBufferSizePx(initParam.useBufferId);
			break;

		case BufferType::depthStencil:

			m_textureSize = DX12GameManager::getDsBufferSizePx(initParam.useBufferId);
			break;
		}

		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void SpriteMaterialData::drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
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
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
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
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}

	// �X�v���C�g�p�̒萔�o�b�t�@���X�V����
	void SpriteMaterialData::updateSpriteConstantBuffer(const tktkMath::Matrix3& worldMatrix) const
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

		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Sprite), constantBufferData);
	}
}
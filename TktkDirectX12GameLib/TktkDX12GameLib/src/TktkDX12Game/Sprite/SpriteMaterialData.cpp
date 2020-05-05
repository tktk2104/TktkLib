#include "TktkDX12Game/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Sprite/SpriteConstantBufferData.h"

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
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_type = BasicDescriptorType::textureBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_id = initParam.useTextureId;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).m_type = BasicDescriptorType::constantBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).m_id = 1U;

		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void SpriteMaterialData::drawSprite(const tktkMath::Matrix3& worldMatrix)
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

		DX12GameManager::updateConstantBuffer(1U, constantBufferData);

		DX12GameManager::setGraphicsPipeLineState(1U);
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, 1U } });
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		DX12GameManager::setVertexBuffer(1U);
		DX12GameManager::setIndexBuffer(1U);
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);
	}
}
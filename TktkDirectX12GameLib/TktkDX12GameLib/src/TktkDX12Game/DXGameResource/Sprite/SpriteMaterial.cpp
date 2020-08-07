#include "TktkDX12Game/DXGameResource/Sprite/SpriteMaterial.h"

#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteMaterial::SpriteMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum)
		: m_spriteMaterialArray(spriteMaterialNum)
	{
		// �X�v���C�g�p�̃��[�g�V�O�l�`�������
		createRootSignature();

		// �X�v���C�g�p�̃O���t�B�b�N�p�C�v���C���X�e�[�g�����
		createGraphicsPipeLineState(shaderFilePaths);

		// �X�v���C�g�p�̒��_�o�b�t�@�����
		DX12GameManager::createVertexBuffer<tktkMath::Vector2>(DX12GameManager::getSystemId(SystemVertexBufferType::Sprite), { tktkMath::vec2Zero, tktkMath::vec2Right, tktkMath::vec2Up, tktkMath::vec2One });

		// �X�v���C�g�p�̃C���f�b�N�X�o�b�t�@�����
		DX12GameManager::createIndexBuffer(DX12GameManager::getSystemId(SystemIndexBufferType::Sprite), { 0U, 1U, 2U, 3U });

		// �X�v���C�g�p�̒萔�o�b�t�@�����
		DX12GameManager::createCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Sprite), SpriteConstantBufferData());
	}

	void SpriteMaterial::create(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_spriteMaterialArray.emplaceAt(id, initParam);
	}

	void SpriteMaterial::drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_spriteMaterialArray.at(id)->drawSprite(drawFuncArgs);
	}

	// �X�v���C�g�p�̃��[�g�V�O�l�`��
	void SpriteMaterial::createRootSignature() const
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(2U);
		{/* �e�N�X�`���p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.rootParamArray.at(0).descriptorTable.resize(1U);
			{
				initParam.rootParamArray.at(0).descriptorTable.at(0).numDescriptors = 1U;
				initParam.rootParamArray.at(0).descriptorTable.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}
		{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(1).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			initParam.rootParamArray.at(1).descriptorTable.resize(1U);
			{
				initParam.rootParamArray.at(1).descriptorTable.at(0).numDescriptors = 1U;
				initParam.rootParamArray.at(1).descriptorTable.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		initParam.samplerDescArray.resize(1U);
		{/* �T���v���[�̐ݒ� */
			initParam.samplerDescArray.at(0).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.samplerDescArray.at(0).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.samplerDescArray.at(0).maxLod = D3D12_FLOAT32_MAX;
			initParam.samplerDescArray.at(0).minLod = 0.0f;
			initParam.samplerDescArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.samplerDescArray.at(0).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		}
		DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::Sprite), initParam);
	}

	// �X�v���C�g�p�̃O���t�B�b�N�p�C�v���C���X�e�[�g
	void SpriteMaterial::createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable = true;
		renderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = false;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::Sprite);

		DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Sprite), initParam, shaderFilePaths);
	}
}
#include "TktkDX12Game/Sprite/Sprite.h"

#include <vector>
#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	Sprite::Sprite(const ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum)
		: m_spriteMaterial(spriteMaterialNum)
	{
		// �X�v���C�g�p�̃��[�g�V�O�l�`�������
		createRootSignature();

		createGraphicsPipeLineState(shaderFilePaths);

		// �X�v���C�g�p�̒��_�o�b�t�@�����
		std::vector<tktkMath::Vector2> vertices{
			tktkMath::vec2Zero,
			tktkMath::vec2Right,
			tktkMath::vec2Up,
			tktkMath::vec2One
		};
		DX12GameManager::createVertexBuffer(1U, vertices);

		// �X�v���C�g�p�̃C���f�b�N�X�o�b�t�@�����
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		DX12GameManager::createIndexBuffer(1U, { 0U, 1U, 2U, 3U });

		// �X�v���C�g�p�̒萔�o�b�t�@�����
		DX12GameManager::createConstantBuffer(1U, SpriteConstantBufferData());
	}

	void Sprite::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_spriteMaterial.create(id, initParam);
	}

	void Sprite::drawSprite(unsigned int spriteMaterialId, const tktkMath::Matrix3& worldMatrix)
	{
		m_spriteMaterial.drawSprite(spriteMaterialId, worldMatrix);
	}

	// �X�v���C�g�p�̃��[�g�V�O�l�`��
	void Sprite::createRootSignature()
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(2U);
		{/* �e�N�X�`���p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.rootParamArray.at(0).descriptorTableArray.resize(1U);
			{
				initParam.rootParamArray.at(0).descriptorTableArray.at(0).numDescriptors = 1;
				initParam.rootParamArray.at(0).descriptorTableArray.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}
		{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(1).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.rootParamArray.at(1).descriptorTableArray.resize(1U);
			{
				initParam.rootParamArray.at(1).descriptorTableArray.at(0).numDescriptors = 1;
				initParam.rootParamArray.at(1).descriptorTableArray.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
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
		DX12GameManager::createRootSignature(1U, initParam);
	}

	// �X�v���C�g�p�̃O���t�B�b�N�p�C�v���C���X�e�[�g
	void Sprite::createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths)
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = true;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = { 
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureId = 1U;

		DX12GameManager::createGraphicsPipeLineState(1U, initParam, shaderFilePaths);
	}
}
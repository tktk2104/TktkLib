#include "TktkDX12Game/Sprite/Sprite.h"

#include <vector>
#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	Sprite::Sprite(const tktk::ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum)
		: m_spriteMaterial(spriteMaterialNum)
	{
		// スプライト用のルートシグネチャを作る
		createRootSignature();

		createGraphicsPipeLineState(shaderFilePaths);

		// スプライト用の頂点バッファを作る
		std::vector<tktkMath::Vector2> vertices{
			tktkMath::Vector2(0.0f, 0.0f),
			tktkMath::Vector2(1.0f, 0.0f),
			tktkMath::Vector2(0.0f, 1.0f),
			tktkMath::Vector2(1.0f, 1.0f)

			/*tktkMath::Vector2(-0.4f, -0.7f),
			tktkMath::Vector2(-0.4f,  0.7f),
			tktkMath::Vector2( 0.4f, -0.7f),
			tktkMath::Vector2( 0.4f,  0.7f)*/

			/*tktkMath::vec2Zero,
			tktkMath::vec2Right,
			tktkMath::vec2Up,
			tktkMath::vec2One*/
		};
		DX12GameManager::createVertexBuffer(1U, vertices);

		// スプライト用のインデックスバッファを作る
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		DX12GameManager::createIndexBuffer(1U, { 0U, 1U, 2U, 3U });//{ 0U, 1U, 2U,  2U, 1U, 3U }

		// スプライト用の定数バッファを作る
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

	// スプライト用のルートシグネチャ
	void Sprite::createRootSignature()
	{
		tktk::RootSignatureInitParam initParam{};
		initParam.m_flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.m_rootParamArray.resize(2U);
		{/* テクスチャ用のルートパラメータ */
			initParam.m_rootParamArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.m_rootParamArray.at(0).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}
		{/* 定数バッファ用のルートパラメータ */
			initParam.m_rootParamArray.at(1).m_shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.m_rootParamArray.at(1).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		initParam.m_samplerDescArray.resize(1U);
		{/* サンプラーの設定 */
			initParam.m_samplerDescArray.at(0).m_addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.m_samplerDescArray.at(0).m_filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.m_samplerDescArray.at(0).m_maxLod = D3D12_FLOAT32_MAX;
			initParam.m_samplerDescArray.at(0).m_minLod = 0.0f;
			initParam.m_samplerDescArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.m_samplerDescArray.at(0).m_comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		}
		tktk::DX12GameManager::createRootSignature(1U, initParam);
	}

	// スプライト用のグラフィックパイプラインステート
	void Sprite::createGraphicsPipeLineState(const tktk::ShaderFilePaths& shaderFilePaths)
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		tktk::GraphicsPipeLineStateInitParam initParam{};
		initParam.m_rasterizerDesc.MultisampleEnable = false;
		initParam.m_rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.m_rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.m_rasterizerDesc.DepthClipEnable = true;
		initParam.m_blendDesc.AlphaToCoverageEnable = false;
		initParam.m_blendDesc.IndependentBlendEnable = false;
		initParam.m_blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.m_inputLayoutArray = { 
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.m_primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.m_renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

		tktk::DX12GameManager::createGraphicsPipeLineState(1U, initParam, shaderFilePaths, 1U);
	}
}
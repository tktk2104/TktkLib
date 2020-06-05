#include "TktkDX12Game/DXGameResource/PostEffect/PostEffectMaterial.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectMaterial::PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, unsigned int postEffectMaterialNum)
		: m_postEffectMaterialArray(postEffectMaterialNum)
	{
		// ���m�N���̃|�X�g�G�t�F�N�g�p�̃��[�g�V�O�l�`�������
		{
			RootSignatureInitParam initParam{};
			initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			initParam.rootParamArray.resize(1U);
			{/* �e�N�X�`���p�̃��[�g�p�����[�^ */
				initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(0).descriptorTableArray.resize(1U);
				{
					initParam.rootParamArray.at(0).descriptorTableArray.at(0).numDescriptors = 1;
					initParam.rootParamArray.at(0).descriptorTableArray.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
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

			DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::PostEffectMonochrome), initParam);
		}

		// ���m�N���̃|�X�g�G�t�F�N�g�p�̃p�C�v���C���X�e�[�g�����
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
			initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::PostEffectMonochrome);

			ShaderFilePaths filePaths{};
			filePaths.vsFilePath = shaderFilePaths.postEffectVSFilePath;
			filePaths.psFilePath = shaderFilePaths.monochromePSFilePath;

			DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::PostEffectMonochrome), initParam, filePaths);
		}
	}

	void PostEffectMaterial::create(unsigned int id, const PostEffectMaterialInitParam& initParam)
	{
		m_postEffectMaterialArray.emplaceAt(id, initParam);
	}

	void PostEffectMaterial::drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterialArray.at(id)->drawPostEffect(drawFuncArgs);
	}
}
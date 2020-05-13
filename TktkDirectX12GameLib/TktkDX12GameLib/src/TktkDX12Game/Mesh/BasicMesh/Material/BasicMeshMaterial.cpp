#include "TktkDX12Game/Mesh/BasicMesh/Material/BasicMeshMaterial.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

namespace tktk
{
	BasicMeshMaterial::BasicMeshMaterial(const tktk::ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum)
		: m_basicMeshMaterialArray(basicMeshMaterialNum)
	{
		createRootSignature();

		createGraphicsPipeLineState(shaderFilePaths);

		// �ʏ탁�b�V���p�̒萔�o�b�t�@�����
		DX12GameManager::createConstantBuffer(2U, BasicMeshConstantBufferData());
	}

	void BasicMeshMaterial::create(unsigned int id, const BasicMeshMaterialInitParam& initparam)
	{
		m_basicMeshMaterialArray.emplaceAt(id, initparam);
	}

	void BasicMeshMaterial::drawUseMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.at(id);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->drawUseMaterial(baseArgs, materialArgs);
	}

	void BasicMeshMaterial::createRootSignature()
	{
		tktk::RootSignatureInitParam initParam{};
		initParam.m_flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		
		//initParam.m_rootParamArray.resize(1U);
		//{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
		//	initParam.m_rootParamArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//D3D12_SHADER_VISIBILITY_VERTEX;
		//	initParam.m_rootParamArray.at(0).m_descriptorTableArray.resize(1U);
		//	{
		//		initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_numDescriptors = 1;
		//		initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		//	}
		//}

		initParam.m_rootParamArray.resize(2U);
		{/* �e�N�X�`���p�̃��[�g�p�����[�^ */
			initParam.m_rootParamArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.m_rootParamArray.at(0).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}
		{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
			initParam.m_rootParamArray.at(1).m_shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.m_rootParamArray.at(1).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}

		initParam.m_samplerDescArray.resize(1U);
		{/* �T���v���[�̐ݒ� */
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
		tktk::DX12GameManager::createRootSignature(2U, initParam);
	}

	void BasicMeshMaterial::createGraphicsPipeLineState(const tktk::ShaderFilePaths& shaderFilePaths)
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
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.m_primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.m_renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

		initParam.m_useDepth = true;
		initParam.m_writeDepth = true;
		initParam.m_depthFunc = D3D12_COMPARISON_FUNC_LESS;

		tktk::DX12GameManager::createGraphicsPipeLineState(2U, initParam, shaderFilePaths, 2U);
	}
}
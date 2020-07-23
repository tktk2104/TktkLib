#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMesh.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMesh::BasicMesh(const std::string& writeShadowMapVsFilePath, unsigned int basicMeshNum)
		: m_basicMeshArray(basicMeshNum)
	{
		// TODO : Mesh�N���X������Ă��̃N���X���������āA���̏�����Mesh�N���X�Ɉړ�����
		// ���b�V�����ʂŎg�p������W�ϊ��萔�o�b�t�@�����
		tktk::DX12GameManager::createCBuffer(tktk::DX12GameManager::getSystemId(tktk::SystemCBufferType::MeshTransform), MeshTransformCbuffer());
		tktk::DX12GameManager::createCBuffer(tktk::DX12GameManager::getSystemId(tktk::SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer());

		createWriteShadowMapRootSignature();
		createWriteShadowMapGraphicsPipeLineState(writeShadowMapVsFilePath);
	
		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̃f�B�X�N���v�^�q�[�v�����
		{
			BasicDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = true;
			initParam.descriptorTableParamArray.resize(1U);

			{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = initParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// 
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::MeshTransform)	},
					{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::BoneMatCbuffer)	}
				};
			}

			DX12GameManager::createBasicDescriptorHeap(DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::BasicMeshShadowMap), initParam);
		}
	}

	void BasicMesh::craete(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_basicMeshArray.emplaceAt(id, initParam);
	}

	void BasicMesh::writeShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData)
	{
		// ���b�V���̍��W�ϊ��Ɏg�p�������萔�o�b�t�@�ɏ�������
		updateMeshTransformCbuffer(transformBufferData);

		// �V���h�E�}�b�v�ւ̏������݂��s��
		m_basicMeshArray.at(id)->writeShadowMap();
	}

	void BasicMesh::drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		// ���b�V���̍��W�ϊ��Ɏg�p�������萔�o�b�t�@�ɏ�������
		updateMeshTransformCbuffer(baseArgs.transformBufferData);

		// ���b�V���̃V���h�E�}�b�v�g�p���邽�߂̏���萔�o�b�t�@�ɏ�������
		updateMeshShadowMapCBuffer(baseArgs.shadowMapBufferData);

		// ���b�V���̃��C�e�B���O�Ɏg�p���郉�C�g����萔�o�b�t�@�ɏ�������
		DX12GameManager::updateLightCBuffer(baseArgs.lightId);

		// ���b�V���̕`����s��
		m_basicMeshArray.at(id)->drawMesh(baseArgs);
	}

	void BasicMesh::createWriteShadowMapRootSignature()
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		initParam.rootParamArray.resize(1U);
		{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.rootParamArray.at(0).descriptorTable = {
				{ 2U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
			};
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
		DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::ShadowMap), initParam);
	}

	void BasicMesh::createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath)
	{
		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = true;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.inputLayoutArray = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		initParam.useDepth = true;
		initParam.writeDepth = true;
		initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
		initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::ShadowMap);

		ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.vsFilePath = writeShadowMapVsFilePath;
		shaderFilePaths.psFilePath = "";

		DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::ShadowMap), initParam, shaderFilePaths);
	}

	void BasicMesh::updateMeshTransformCbuffer(const MeshTransformCbuffer& transformBufferData)
	{
		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::MeshTransform), transformBufferData);
	}

	void BasicMesh::updateMeshShadowMapCBuffer(const MeshShadowMapCBuffer& shadowMapBufferData)
	{
		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::MeshShadowMap), shadowMapBufferData);
	}
}
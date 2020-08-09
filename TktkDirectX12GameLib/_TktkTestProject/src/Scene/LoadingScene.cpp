#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"
#include "../Enum/_ResourceIds/ResourceIds.h"
#include "../TutorialCode/GameObject/ElementShape/VertexColor2DPolygonConstantBufferData.h"

void LoadingScene::start()
{
	// �e�N�X�`����ǂݍ���
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(toInt(TextureBufferId::Test), "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// �X�v���C�g�̃}�e���A�������
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId	= toInt(BasicDescriptorHeapId::TestTexture);
		initParam.srvBufferType				= tktk::BufferType::texture;
		initParam.useBufferId				= toInt(TextureBufferId::Test);
		/*initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDsBufferType::ShadowMap);*/

		tktk::DX12GameManager::createSpriteMaterial(toInt(SpriteMaterialId::Test), initParam);
	}

	// ���b�V�������[�h����
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.filePath = "res/Model/�����~�N.pmd";
		loadArgs.createDescriptorHeapIdStartNum		= toInt(BasicDescriptorHeapId::MikuMatStart);
		loadArgs.createVertexBufferId				= toInt(VertexBufferId::Miku);
		loadArgs.createIndexBufferId				= toInt(IndexBufferId::Miku);
		loadArgs.createBasicMeshId					= toInt(BasicMeshId::Miku);
		loadArgs.createSkeletonId					= toInt(SkeletonId::Miku);
		loadArgs.createBasicMeshMaterialIdStartNum	= toInt(BasicMeshMaterialId::MikuMatStart);;
		loadArgs.createTextureIdStartNum			= toInt(TextureBufferId::MikuTexStart);

		auto result = tktk::DX12GameManager::loadPmd(loadArgs);

		if (result.createDescriptorHeapIdEndNum		!= toInt(BasicDescriptorHeapId::MikuMatEnd)	||
			result.createBasicMeshMaterialIdEndNum	!= toInt(BasicMeshMaterialId::MikuMatEnd)	||
			result.createTextureIdEndNum			!= toInt(TextureBufferId::MikuTexEnd)				)
		{
			//throw std::runtime_error("load Pmd error");
		}
	}

	// ���[�V���������[�h����
	{
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion1), "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion2), "res/Motion/motion.vmd");
	}

	// �����_�[�^�[�Q�b�g�o�b�t�@�����
	{
		tktk::DX12GameManager::createRtBuffer(toInt(RenderTargetBufferId::PostEffectTest), tktk::DX12GameManager::getWindowSize(), tktkMath::colorRed);
	}

	// �����_�[�^�[�Q�b�g�r���[�����
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type	= tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id	= toInt(RenderTargetBufferId::PostEffectTest);

		tktk::DX12GameManager::createRtvDescriptorHeap(toInt(RtvDescriptorHeapId::PostEffectTest), initParam);
	}

	// ���m�N���̃|�X�g�G�t�F�N�g�p�̃f�B�X�N���v�^�q�[�v�����
	{
		// �f�B�X�N���v�^�q�[�v�����
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = tktk::BasicDescriptorType::textureBuffer;

			// �����_�[�^�[�Q�b�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::renderTarget,		toInt(RenderTargetBufferId::PostEffectTest) }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(toInt(BasicDescriptorHeapId::PostEffectTest), descriptorHeapInitParam);
	}

	// ���m�N���̃|�X�g�G�t�F�N�g�����
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = toInt(BasicDescriptorHeapId::PostEffectTest);

		tktk::DX12GameManager::createPostEffectMaterial(toInt(PostEffectMaterialId::PostEffectTest), initParam);
	}

	// �T�E���h�����[�h����
	{
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestSe), "res/Sound/damage.wav");
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestBgm), "res/Sound/kendo.wav");
	}

	// �J���������
	{
		// �ʏ�J����
		tktk::DX12GameManager::createCamera(toInt(CameraId::Basic));

		// �V���h�E�}�b�v�J����
		tktk::DX12GameManager::createCamera(toInt(CameraId::ShadowMap));
	}

	// ���C�g�����
	{
		// �ʏ탉�C�g
		tktk::DX12GameManager::createLight(
			toInt(LightId::Basic),
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.0f }
		);
	}

	// ���_�J���[�V�F�[�_�[�p�̒萔�o�b�t�@�����
	tktk::DX12GameManager::createCBuffer(toInt(CbufferId::VertexColorPolygon), VertexColor2DPolygonConstantBufferData());

	// ���_�J���[�V�F�[�_�[�p�̃f�B�X�N���v�^�q�[�v�����
	{
		// �f�B�X�N���v�^�q�[�v�����
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			cbufferViewDescriptorParam.type = tktk::BasicDescriptorType::constantBuffer;

			// ���_�J���[�萔�o�b�t�@�̂P���
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::constant,		toInt(CbufferId::VertexColorPolygon) }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(toInt(BasicDescriptorHeapId::VertexColorPolygon), descriptorHeapInitParam);
	}

	// ���_�J���[�V�F�[�_�[�p�̃��[�g�V�O�l�`�������
	{
		tktk::RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(1U);
		{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			initParam.rootParamArray.at(0).descriptorTable.resize(1U);
			{
				initParam.rootParamArray.at(0).descriptorTable.at(0).numDescriptors = 1U;
				initParam.rootParamArray.at(0).descriptorTable.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		initParam.samplerDescArray.resize(0U);
		//{/* �T���v���[�̐ݒ� */
		//	initParam.samplerDescArray.at(0).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		//	initParam.samplerDescArray.at(0).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		//	initParam.samplerDescArray.at(0).maxLod = D3D12_FLOAT32_MAX;
		//	initParam.samplerDescArray.at(0).minLod = 0.0f;
		//	initParam.samplerDescArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		//	initParam.samplerDescArray.at(0).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		//}
		tktk::DX12GameManager::createRootSignature(toInt(RootSignatureId::VertexColorPolygon), initParam);
	}

	// ���_�J���[�V�F�[�_�[�p�̃p�C�v���C���X�e�[�g�����
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable			= true;
		renderTargetBlendDesc.SrcBlend				= D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend				= D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp				= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha			= D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha		= D3D12_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha			= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOpEnable			= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		tktk::PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = false;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = true;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureId = toInt(RootSignatureId::VertexColorPolygon);

		tktk::ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.vsFilePath = "res/Shader/VertexColor2DPolygonVertexShader.cso";
		shaderFilePaths.psFilePath = "res/Shader/VertexColor2DPolygonPixelShader.cso";

		tktk::DX12GameManager::createPipeLineState(toInt(PipeLineStateId::VertexColorPolygon), initParam, shaderFilePaths);
	}

	// 2D���C���}�e���A�������
	{
		tktk::Line2DMaterialDataInitParam initParam;
		initParam.createVertexBufferId = toInt(VertexBufferId::ElementShapeGuide);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::ElementShapeGuide), initParam);

		initParam.createVertexBufferId = toInt(VertexBufferId::CollideDebug1);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::CollideDebug1), initParam);

		initParam.createVertexBufferId = toInt(VertexBufferId::CollideDebug2);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::CollideDebug2), initParam);
	}

	//// ���̃��b�V���}�e���A�����R�s�[����
	//for (unsigned int i = toInt(BasicMeshMaterialId::ElementSphereStart); i <= toInt(BasicMeshMaterialId::ElementSphereEnd); i++)
	//{
	//	tktk::DX12GameManager::copyBasicMeshMaterial(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshMaterialType::Sphere));
	//}

	//// ���̃��b�V�����R�s�[����
	//for (unsigned int i = toInt(BasicMeshId::ElementSphereStart); i <= toInt(BasicMeshId::ElementSphereEnd); i++)
	//{
	//	tktk::DX12GameManager::copyBasicMesh(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshType::Sphere));
	//}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// �ǂݍ��݃V�[���𖳌��ɂ���
	tktk::DX12GameManager::disableScene(toInt(SceneId::Loading));

	// ���C���V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(toInt(SceneId::Main));
}

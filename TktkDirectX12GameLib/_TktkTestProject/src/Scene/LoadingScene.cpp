#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"

#include "../Enum/_ResourceIds/ResourceIds.h"

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

	// ���̃��b�V���}�e���A�����R�s�[����
	for (unsigned int i = toInt(BasicMeshMaterialId::ElementSphereStart); i <= toInt(BasicMeshMaterialId::ElementSphereEnd); i++)
	{
		tktk::DX12GameManager::copyBasicMeshMaterial(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshMaterialType::Sphere));
	}

	// ���̃��b�V�����R�s�[����
	for (unsigned int i = toInt(BasicMeshId::ElementSphereStart); i <= toInt(BasicMeshId::ElementSphereEnd); i++)
	{
		tktk::DX12GameManager::copyBasicMesh(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshType::Sphere));
	}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// �ǂݍ��݃V�[���𖳌��ɂ���
	tktk::DX12GameManager::disableScene(toInt(SceneId::Loading));

	// ���C���V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(toInt(SceneId::Main));
}

#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"

void LoadingScene::start()
{
	// �e�N�X�`����ǂݍ���
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(0U, "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// �X�v���C�g�̃}�e���A�������
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId = 1U;
		initParam.srvBufferType = tktk::BufferType::texture;
		initParam.useBufferId = 0U;
		/*initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDsBufferType::ShadowMap);*/

		tktk::DX12GameManager::createSpriteMaterial(0U, initParam);
	}

	// ���b�V�������[�h����
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.filePath = "res/Model/�����~�N.pmd";
		loadArgs.createDescriptorHeapIdStartNum = 2U;
		loadArgs.createVertexBufferId = 0U;
		loadArgs.createIndexBufferId = 0U;
		loadArgs.createBasicMeshId = 0U;
		loadArgs.createSkeletonId = 0U;
		loadArgs.createBasicMeshMaterialIdStartNum = 0U;
		loadArgs.createTextureIdStartNum = 1U;

		auto result = tktk::DX12GameManager::loadPmd(loadArgs);

		if (result.createBasicMeshMaterialIdEndNum == 16U)
		{
			//throw std::runtime_error("load Pmd error");
		}
	}

	// ���[�V���������[�h����
	{
		tktk::DX12GameManager::loadMotion(0U, "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotion(1U, "res/Motion/motion.vmd");
	}

	// �����_�[�^�[�Q�b�g�o�b�t�@�����
	{
		tktk::DX12GameManager::createRtBuffer(0U, tktk::DX12GameManager::getWindowSize(), tktkMath::colorRed);
	}

	// �����_�[�^�[�Q�b�g�r���[�����
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type = tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id = 0U;

		tktk::DX12GameManager::createRtvDescriptorHeap(0U, initParam);
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
				{ tktk::BufferType::renderTarget,		0U }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(0U, descriptorHeapInitParam);
	}

	// ���m�N���̃|�X�g�G�t�F�N�g�����
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = 0U;

		tktk::DX12GameManager::createPostEffectMaterial(0U, initParam);
	}

	// �T�E���h�����[�h����
	{
		tktk::DX12GameManager::loadSound(0U, "res/Sound/damage.wav");
		tktk::DX12GameManager::loadSound(1U, "res/Sound/kendo.wav");
	}

	// �J���������
	{
		// �ʏ�J����
		tktk::DX12GameManager::createCamera(0U);

		// �V���h�E�}�b�v�J����
		tktk::DX12GameManager::createCamera(1U);
	}

	// ���C�g�����
	{
		// �ʏ�J����
		tktk::DX12GameManager::createLight(
			0U,
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.0f }
		);
	}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// �ǂݍ��݃V�[���𖳌��ɂ���
	tktk::DX12GameManager::disableScene(0U);

	// ���C���V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(1U);
}

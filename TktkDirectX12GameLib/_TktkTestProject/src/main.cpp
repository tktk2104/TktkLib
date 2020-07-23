#include <TktkFileIoLibDefinition.h>
#include <TktkMathLibDefinition.h>
#include <TktkDX12WrappingLibDefinition.h>
#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

#include <TktkDX12Game/Component/ComponentManager.h>
#include <TktkDX12Game/Component/ComponentBase.h>

#include "Scene/LoadingScene.h"
#include "Scene/MainScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	// �uDX12GameManager�v�̏����ݒ������
	{
		tktk::DX12GameManagerInitParam initParam{};

		{
			auto& resourceInitParam = initParam.dx3dResParam;

			resourceInitParam.viewPortNum = 0U;
			resourceInitParam.scissorRectNum = 0U;
			resourceInitParam.pipeLineStateNum = 0U;
			resourceInitParam.rootSignatureNum = 0U;

			{
				auto& descriptorHeapInitParam = resourceInitParam.descriptorHeapInitParam;

				descriptorHeapInitParam.basicDescriptorHeapNum = 19U;
				descriptorHeapInitParam.rtvDescriptorHeapNum = 1U;
				descriptorHeapInitParam.dsvDescriptorHeapNum = 0U;
			}

			{
				auto& bufferResourceInitParam = resourceInitParam.bufferResourceInitParam;

				bufferResourceInitParam.vertexBufferNum = 1U;
				bufferResourceInitParam.indexBufferNum = 1U;
				bufferResourceInitParam.constantBufferNum = 0U;
				bufferResourceInitParam.textureBufferNum = 17U;
				bufferResourceInitParam.depthStencilBufferNum = 0U;
				bufferResourceInitParam.renderTargetBufferNum = 1U;
			}
		}

		{
			auto& windowParam = initParam.windowParam;

			windowParam.hInstance	= hInstance;
			windowParam.nCmdShow	= nCmdShow;
			windowParam.windowName	= "TestProject";
			windowParam.windowSize	= { 1920.0f, 1080.0f };
		}
		
		{
			auto& dxGameResourceNum = initParam.dxGameResourceNum;

			dxGameResourceNum.sceneNum				= 2U;
			dxGameResourceNum.soundNum				= 2U;
			dxGameResourceNum.spriteNum				= 1U;
			dxGameResourceNum.basicMeshNum			= 1U;
			dxGameResourceNum.basicMeshMaterialNum	= 17U;
			dxGameResourceNum.skeletonNum			= 1U;
			dxGameResourceNum.motionNum				= 2U;
			dxGameResourceNum.postEffectMaterialNum = 1U;
			dxGameResourceNum.cameraNum				= 2U;
			dxGameResourceNum.lightNum				= 1U;
		}

		// DX12GameManager�̃Z�b�g�A�b�v
		tktk::DX12GameManager::initialize(initParam);
	}

	// �V�[����ǉ�����
	tktk::DX12GameManager::addScene<LoadingScene>(0U);
	tktk::DX12GameManager::addScene<MainScene>(1U);

	// �ǂݍ��݃V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(0U);

	// �Փ˔���̑g�ݍ��킹��ݒ肷��
	tktk::DX12GameManager::addCollisionGroup(1, 2);

	// �v���O�����J�n
	tktk::DX12GameManager::run();

	return 0;
}
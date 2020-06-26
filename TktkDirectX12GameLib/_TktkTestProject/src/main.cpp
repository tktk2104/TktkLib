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
	// 「DX12GameManager」の初期設定をする
	{
		tktk::DescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.basicDescriptorHeapNum	= 19U;
		descriptorHeapInitParam.rtvDescriptorHeapNum	= 1U;
		descriptorHeapInitParam.dsvDescriptorHeapNum	= 0U;

		tktk::BufferResourceInitParam bufferResourceInitParam{};
		bufferResourceInitParam.vertexBufferNum			= 1U;
		bufferResourceInitParam.indexBufferNum			= 1U;
		bufferResourceInitParam.constantBufferNum		= 0U;
		bufferResourceInitParam.textureBufferNum		= 17U;
		bufferResourceInitParam.depthStencilBufferNum	= 0U;
		bufferResourceInitParam.renderTargetBufferNum	= 1U;

		tktk::DX3DResourceInitParam resourceInitParam{};
		resourceInitParam.viewPortNum				= 0U;
		resourceInitParam.scissorRectNum			= 0U;
		resourceInitParam.pipeLineStateNum			= 0U;
		resourceInitParam.rootSignatureNum			= 0U;
		resourceInitParam.descriptorHeapInitParam	= descriptorHeapInitParam;
		resourceInitParam.bufferResourceInitParam	= bufferResourceInitParam;

		tktk::DX3DBaseObjectsInitParam initParam{};
		initParam.resourceInitParam = resourceInitParam;
		initParam.spriteNum					= 1U;
		initParam.basicMeshNum				= 1U;
		initParam.basicMeshMaterialNum		= 17U;
		initParam.skeletonNum				= 1U;
		initParam.motionNum					= 2U;
		initParam.postEffectMaterialNum		= 1U;
		initParam.soundDataNum				= 2U;

		tktk::DX12GameManager::initialize(2U, initParam, { hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } });
	}

	// シーンを追加する
	tktk::DX12GameManager::addScene<LoadingScene>(0U);
	tktk::DX12GameManager::addScene<MainScene>(1U);

	// 読み込みシーンを有効にする
	tktk::DX12GameManager::enableScene(0U);

	// 衝突判定の組み合わせを設定する
	tktk::DX12GameManager::addCollisionGroup(1, 2);

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}
#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"

void LoadingScene::start()
{
	// テクスチャを読み込む
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(0U, "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// スプライトのマテリアルを作る
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId = 1U;
		/*initParam.srvBufferType = tktk::BufferType::texture;
		initParam.useBufferId = 0U;*/
		initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDepthStencilBufferType::ShadowMap);

		tktk::DX12GameManager::createSpriteMaterial(0U, initParam);
	}

	// メッシュをロードする
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.m_filePath = "res/Model/初音ミク.pmd";
		loadArgs.createDescriptorHeapIdStartNum = 2U;
		loadArgs.createVertexBufferId = 0U;
		loadArgs.createIndexBufferId = 0U;
		loadArgs.createBasicMeshId = 0U;
		loadArgs.createSkeletonId = 0U;
		loadArgs.createBasicMeshMaterialIdStartNum = 0U;
		loadArgs.loadTextureIdStartNum = 1U;

		auto result = tktk::DX12GameManager::loadPmd(loadArgs);

		if (result.createBasicMeshMaterialIdEndNum == 16U)
		{
			//throw std::runtime_error("load Pmd error");
		}
	}

	// モーションをロードする
	{
		tktk::DX12GameManager::loadMotion(0U, "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotion(1U, "res/Motion/motion.vmd");
	}

	// レンダーターゲットバッファを作る
	{
		tktk::DX12GameManager::createRenderTargetBuffer(0U, tktk::DX12GameManager::getWindowSize(), tktkMath::colorRed);
	}

	// レンダーターゲットビューを作る
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type = tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id = 0U;

		tktk::DX12GameManager::createRtvDescriptorHeap(0U, initParam);
	}

	// モノクロのポストエフェクト用のディスクリプタヒープを作る
	{
		// ディスクリプタヒープを作る
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = tktk::BasicDescriptorType::textureBuffer;

			// レンダーターゲットテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::renderTarget,		0U }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(0U, descriptorHeapInitParam);
	}

	// モノクロのポストエフェクトを作る
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = 0U;

		tktk::DX12GameManager::createPostEffectMaterial(0U, initParam);
	}

	// サウンドをロードする
	{
		tktk::DX12GameManager::loadSound(0U, "res/Sound/damage.wav");
		tktk::DX12GameManager::loadSound(1U, "res/Sound/kendo.wav");
	}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// 読み込みシーンを無効にする
	tktk::DX12GameManager::disableScene(0U);

	// メインシーンを有効にする
	tktk::DX12GameManager::enableScene(1U);
}

#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"

#include "../Enum/_ResourceIds/ResourceIds.h"

void LoadingScene::start()
{
	// テクスチャを読み込む
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(toInt(TextureBufferId::Test), "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// スプライトのマテリアルを作る
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId	= toInt(BasicDescriptorHeapId::TestTexture);
		initParam.srvBufferType				= tktk::BufferType::texture;
		initParam.useBufferId				= toInt(TextureBufferId::Test);
		/*initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDsBufferType::ShadowMap);*/

		tktk::DX12GameManager::createSpriteMaterial(toInt(SpriteMaterialId::Test), initParam);
	}

	// メッシュをロードする
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.filePath = "res/Model/初音ミク.pmd";
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

	// モーションをロードする
	{
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion1), "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion2), "res/Motion/motion.vmd");
	}

	// レンダーターゲットバッファを作る
	{
		tktk::DX12GameManager::createRtBuffer(toInt(RenderTargetBufferId::PostEffectTest), tktk::DX12GameManager::getWindowSize(), tktkMath::colorRed);
	}

	// レンダーターゲットビューを作る
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type	= tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id	= toInt(RenderTargetBufferId::PostEffectTest);

		tktk::DX12GameManager::createRtvDescriptorHeap(toInt(RtvDescriptorHeapId::PostEffectTest), initParam);
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
				{ tktk::BufferType::renderTarget,		toInt(RenderTargetBufferId::PostEffectTest) }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(toInt(BasicDescriptorHeapId::PostEffectTest), descriptorHeapInitParam);
	}

	// モノクロのポストエフェクトを作る
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = toInt(BasicDescriptorHeapId::PostEffectTest);

		tktk::DX12GameManager::createPostEffectMaterial(toInt(PostEffectMaterialId::PostEffectTest), initParam);
	}

	// サウンドをロードする
	{
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestSe), "res/Sound/damage.wav");
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestBgm), "res/Sound/kendo.wav");
	}

	// カメラを作る
	{
		// 通常カメラ
		tktk::DX12GameManager::createCamera(toInt(CameraId::Basic));

		// シャドウマップカメラ
		tktk::DX12GameManager::createCamera(toInt(CameraId::ShadowMap));
	}

	// ライトを作る
	{
		// 通常ライト
		tktk::DX12GameManager::createLight(
			toInt(LightId::Basic),
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.0f }
		);
	}

	// 球体メッシュマテリアルをコピーする
	for (unsigned int i = toInt(BasicMeshMaterialId::ElementSphereStart); i <= toInt(BasicMeshMaterialId::ElementSphereEnd); i++)
	{
		tktk::DX12GameManager::copyBasicMeshMaterial(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshMaterialType::Sphere));
	}

	// 球体メッシュをコピーする
	for (unsigned int i = toInt(BasicMeshId::ElementSphereStart); i <= toInt(BasicMeshId::ElementSphereEnd); i++)
	{
		tktk::DX12GameManager::copyBasicMesh(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshType::Sphere));
	}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// 読み込みシーンを無効にする
	tktk::DX12GameManager::disableScene(toInt(SceneId::Loading));

	// メインシーンを有効にする
	tktk::DX12GameManager::enableScene(toInt(SceneId::Main));
}

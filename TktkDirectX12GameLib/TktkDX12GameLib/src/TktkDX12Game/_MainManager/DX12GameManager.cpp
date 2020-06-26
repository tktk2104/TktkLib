#include "TktkDX12Game/_MainManager/DX12GameManager.h"

#include <TktkDX12Wrapper/Graphics/Window/Window.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h>
#include "TktkDX12Game/GameObject/GameObjectManager.h"
#include "TktkDX12Game/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/DXGameResource.h"
#include "TktkDX12Game/Sound/SoundPlayer.h"
#include "TktkDX12Game/Input/Keyboard/Keyboard.h"

namespace tktk
{
	std::unique_ptr<SceneManager>			DX12GameManager::m_sceneManager;
	std::unique_ptr<GameObjectManager>		DX12GameManager::m_gameObjectManager;
	std::unique_ptr<ComponentManager>		DX12GameManager::m_componentManager;
	std::unique_ptr<Window>					DX12GameManager::m_window;
	std::unique_ptr<DX3DBaseObjects>		DX12GameManager::m_dx3dBaseObjects;
	std::unique_ptr<DXGameResource>			DX12GameManager::m_dxGameResource;
	std::unique_ptr<SoundPlayer>			DX12GameManager::m_soundPlayer;
	std::unique_ptr<Keyboard>				DX12GameManager::m_keyboard;

	void DX12GameManager::initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath)
	{
		m_sceneManager			= std::make_unique<SceneManager>(sceneNum);
		m_gameObjectManager		= std::make_unique<GameObjectManager>();
		m_componentManager		= std::make_unique<ComponentManager>();
		m_window				= std::make_unique<Window>(windowInitParam);
		m_dx3dBaseObjects		= std::make_unique<DX3DBaseObjects>(dx3dInitParam, m_window->getHWND(), windowInitParam.windowSize, tktkMath::colorBlue);

		{
			DXGameResourceInitParam initParam;
			initParam.spriteShaderFilePaths.vsFilePath		= tktkLibResFolderPath + "TktkLibRes/shader/SpriteVertexShader.cso";
			initParam.spriteShaderFilePaths.psFilePath		= tktkLibResFolderPath + "TktkLibRes/shader/SpritePixelShader.cso";
			initParam.basicMeshShaderFilePaths.vsFilePath	= tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshVertexShader.cso";
			initParam.basicMeshShaderFilePaths.psFilePath	= tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshPixelShader.cso";
			initParam.writeShadowMapVsFilePath				= tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshShadowVertexShader.cso";

			initParam.postEffectShaderFilePaths.postEffectVSFilePath = tktkLibResFolderPath + "TktkLibRes/shader/PostEffectVertexShader.cso";
			initParam.postEffectShaderFilePaths.monochromePSFilePath = tktkLibResFolderPath + "TktkLibRes/shader/MonochromePixelShader.cso";

			initParam.spriteNum				= dx3dInitParam.spriteNum;
			initParam.basicMeshNum			= dx3dInitParam.basicMeshNum;
			initParam.basicMeshMaterialNum	= dx3dInitParam.basicMeshMaterialNum;
			initParam.skeletonNum			= dx3dInitParam.skeletonNum;
			initParam.motionNum				= dx3dInitParam.motionNum;
			initParam.postEffectMaterialNum = dx3dInitParam.postEffectMaterialNum;

			m_dxGameResource = std::make_unique<DXGameResource>(initParam);
		}
		m_soundPlayer	= std::make_unique<SoundPlayer>(dx3dInitParam.soundDataNum);
		m_keyboard		= std::make_unique<Keyboard>(windowInitParam.hInstance, m_window->getHWND());

		// シャドウマップの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = windowInitParam.windowSize;//{ 1024.0f, 1024.0f };
			initParam.useAsShaderResource = true;

			createDepthStencilBuffer(getSystemId(SystemDepthStencilBufferType::ShadowMap), initParam);
		}

		// シャドウマップの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemId(SystemDepthStencilBufferType::ShadowMap) });

			createDsvDescriptorHeap(getSystemId(SystemDsvDescriptorHeapType::ShadowMap), initParam);
		}
	}

	void DX12GameManager::run()
	{
		MSG msg{};

		while (true)
		{
			bool canRunDX12Func = true;

			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				switch (msg.message)
				{
				case WM_MOUSEMOVE:
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_LBUTTONDBLCLK:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_RBUTTONDBLCLK:
				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_MBUTTONDBLCLK:
				case WM_XBUTTONDOWN:
				case WM_XBUTTONUP:
				case WM_XBUTTONDBLCLK:
				case WM_MOUSEWHEEL:
				case WM_MOUSEHWHEEL:
				case WM_NCMOUSEMOVE:
				case WM_NCLBUTTONDOWN:
				case WM_NCLBUTTONUP:
				case WM_NCLBUTTONDBLCLK:
				case WM_NCRBUTTONDOWN:
				case WM_NCRBUTTONUP:
				case WM_NCRBUTTONDBLCLK:
				case WM_NCMBUTTONDOWN:
				case WM_NCMBUTTONUP:
				case WM_NCMBUTTONDBLCLK:
				case WM_NCXBUTTONDOWN:
				case WM_NCXBUTTONUP:
				case WM_NCXBUTTONDBLCLK:
				case WM_KEYFIRST:
				case WM_KEYUP:
				case WM_CHAR:
				case WM_DEADCHAR:
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_SYSCHAR:
				case WM_SYSDEADCHAR:
				case WM_UNICHAR:

					break;

				default:

					// 処理かっ飛ばし
					canRunDX12Func = false;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (canRunDX12Func)
			{
				m_keyboard->update();
				m_sceneManager->update();
				m_gameObjectManager->update();
				m_componentManager->update();
				m_soundPlayer->update();

				m_dx3dBaseObjects->beginDraw();
				m_componentManager->draw();
				m_dx3dBaseObjects->endDraw();
			}
		}

		m_soundPlayer->finalize();
	}

	const tktkMath::Vector2& DX12GameManager::getWindowSize()
	{
		return m_window->getWindowSize();
	}

	void DX12GameManager::enableScene(unsigned int id)
	{
		m_sceneManager->enableScene(id);
	}

	void DX12GameManager::disableScene(unsigned int id)
	{
		m_sceneManager->disableScene(id);
	}

	GameObjectPtr DX12GameManager::createGameObject()
	{
		return m_gameObjectManager->createGameObject();
	}

	GameObjectPtr DX12GameManager::findGameObjectWithTag(int tag)
	{
		return m_gameObjectManager->findGameObjectWithTag(tag);
	}
	
	std::forward_list<GameObjectPtr> DX12GameManager::findGameObjectWithTags(int tag)
	{
		return m_gameObjectManager->findGameObjectsWithTag(tag);
	}

	void DX12GameManager::addCollisionGroup(int firstGroup, int secondGroup)
	{
		m_componentManager->addCollisionGroup(firstGroup, secondGroup);
	}

	void DX12GameManager::executeCommandList()
	{
		m_dx3dBaseObjects->executeCommandList();
	}

	void DX12GameManager::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_dx3dBaseObjects->setBackGroundColor(backGroundColor);
	}

	void DX12GameManager::setRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRenderTarget(rtvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::unSetRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->unSetRenderTarget(rtvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::unSetDepthStencil(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->unSetDepthStencil(dsvDescriptorHeapId);
	}

	void DX12GameManager::setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRenderTargetAndDepthStencil(rtvDescriptorHeapId, dsvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setOnlyDepthStencil(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->setOnlyDepthStencil(dsvDescriptorHeapId);
	}

	void DX12GameManager::setBackBuffer()
	{
		m_dx3dBaseObjects->setBackBuffer();
	}

	void DX12GameManager::setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->setBackBufferAndDepthStencil(dsvDescriptorHeapId);
	}

	void DX12GameManager::setViewport(unsigned int id)
	{
		m_dx3dBaseObjects->setViewport(id);
	}

	void DX12GameManager::setScissorRect(unsigned int id)
	{
		m_dx3dBaseObjects->setScissorRect(id);
	}

	void DX12GameManager::setPipeLineState(unsigned int id)
	{
		m_dx3dBaseObjects->setPipeLineState(id);
	}

	void DX12GameManager::setVertexBuffer(unsigned int id)
	{
		m_dx3dBaseObjects->setVertexBuffer(id);
	}

	void DX12GameManager::setIndexBuffer(unsigned int id)
	{
		m_dx3dBaseObjects->setIndexBuffer(id);
	}

	void DX12GameManager::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_dx3dBaseObjects->setDescriptorHeap(heapParamArray);
	}

	void DX12GameManager::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_dx3dBaseObjects->setPrimitiveTopology(topology);
	}

	void DX12GameManager::drawIndexedInstanced(unsigned int indexCountPerInstance, unsigned int instanceCount, unsigned int startIndexLocation, unsigned int baseVertexLocation, unsigned int startInstanceLocation)
	{
		m_dx3dBaseObjects->drawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}

	void DX12GameManager::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dx3dBaseObjects->createRootSignature(id, initParam);
	}

	void DX12GameManager::createPipeLineState(unsigned int graphicsPipeLineId, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dx3dBaseObjects->createPipeLineState(graphicsPipeLineId, initParam, shaderFilePath);
	}

	void DX12GameManager::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dx3dBaseObjects->createIndexBuffer(id, indices);
	}

	void DX12GameManager::createRenderTargetBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_dx3dBaseObjects->createRenderTargetBuffer(id, renderTargetSize, clearColor);
	}

	void DX12GameManager::createDepthStencilBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam)
	{
		m_dx3dBaseObjects->createDepthStencilBuffer(id, initParam);
	}

	void DX12GameManager::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createBasicDescriptorHeap(id, initParam);
	}

	void DX12GameManager::createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createRtvDescriptorHeap(id, initParam);
	}

	void DX12GameManager::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createDsvDescriptorHeap(id, initParam);
	}

	void DX12GameManager::cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dx3dBaseObjects->cpuPriorityCreateTextureBuffer(id, formatParam, dataParam);
	}

	void DX12GameManager::gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dx3dBaseObjects->gpuPriorityCreateTextureBuffer(id, formatParam, dataParam);
	}

	void DX12GameManager::cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dx3dBaseObjects->cpuPriorityLoadTextureBuffer(id, texDataPath);
	}

	void DX12GameManager::gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dx3dBaseObjects->gpuPriorityLoadTextureBuffer(id, texDataPath);
	}

	void DX12GameManager::clearRenderTarget(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dx3dBaseObjects->clearRenderTarget(id, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX12GameManager::getTextureSize(unsigned int id)
	{
		return m_dx3dBaseObjects->getTextureSize(id);
	}

	const tktkMath::Vector2& DX12GameManager::getDepthStencilSize(unsigned int id)
	{
		return m_dx3dBaseObjects->getDepthStencilSize(id);
	}

	const tktkMath::Vector2& DX12GameManager::getRenderTargetSize(unsigned int id)
	{
		return m_dx3dBaseObjects->getRenderTargetSize(id);
	}

	void DX12GameManager::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_dxGameResource->createSpriteMaterial(id, initParam);
	}

	void DX12GameManager::drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawSprite(id, drawFuncArgs);
	}

	void DX12GameManager::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_dxGameResource->createBasicMesh(id, initParam);
	}

	void DX12GameManager::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam)
	{
		m_dxGameResource->createBasicMeshMaterial(id, initParam);
	}

	void DX12GameManager::writeBasicMeshShadowMap(unsigned int id, const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->writeBasicMeshShadowMap(id, baseArgs);
	}

	void DX12GameManager::setMaterialData(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->setMaterialData(id, baseArgs);
	}

	void DX12GameManager::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->drawBasicMesh(id, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DX12GameManager::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return m_dxGameResource->loadPmd(args);
	}

	void DX12GameManager::createSkeleton(unsigned int id, const SkeletonInitParam& initParam)
	{
		m_dxGameResource->createSkeleton(id, initParam);
	}

	void DX12GameManager::updateBoneMatrixCbuffer(unsigned int id)
	{
		m_dxGameResource->updateBoneMatrixCbuffer(id);
	}

	void DX12GameManager::loadMotion(unsigned int id, const std::string& motionFileName)
	{
		m_dxGameResource->loadMotion(id, motionFileName);
	}

	void DX12GameManager::updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame)
	{
		m_dxGameResource->updateMotion(skeletonId, motionId, curFrame);
	}

	void DX12GameManager::createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam)
	{
		m_dxGameResource->createPostEffectMaterial(id, initParam);
	}

	void DX12GameManager::drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawPostEffect(id, drawFuncArgs);
	}

	void DX12GameManager::loadSound(unsigned int id, const std::string& fileName)
	{
		m_soundPlayer->load(id, fileName);
	}

	void DX12GameManager::playSound(unsigned int id, bool loopPlay)
	{
		m_soundPlayer->play(id, loopPlay);
	}

	void DX12GameManager::stopSound(unsigned int id)
	{
		m_soundPlayer->stop(id);
	}

	void DX12GameManager::pauseSound(unsigned int id)
	{
		m_soundPlayer->pause(id);
	}

	void DX12GameManager::setMasterVolume(float volume)
	{
		m_soundPlayer->setMasterVolume(volume);
	}

	bool DX12GameManager::isPush(KeybordKeyType keyType)
	{
		return m_keyboard->isPush(keyType);
	}

	bool DX12GameManager::isTrigger(KeybordKeyType keyType)
	{
		return m_keyboard->isTrigger(keyType);
	}

	unsigned int DX12GameManager::getSystemId(SystemViewportType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemScissorRectType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemVertexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemIndexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemConstantBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemTextureBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemDepthStencilBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemBasicDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemRtvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemDsvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemRootSignatureType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemPipeLineStateType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	void DX12GameManager::createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dx3dBaseObjects->createVertexBuffer(id, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX12GameManager::createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dx3dBaseObjects->createConstantBuffer(id, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX12GameManager::updateConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dx3dBaseObjects->updateConstantBuffer(id, constantBufferTypeSize, constantBufferDataTopPos);
	}
}
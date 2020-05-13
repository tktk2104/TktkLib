#include "TktkDX12Game/_MainManager/DX12GameManager.h"

#include <TktkDX12Wrapper/Graphics/Window/Window.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h>
#include "TktkDX12Game/Sprite/Sprite.h"
#include "TktkDX12Game/Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "TktkDX12Game/Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "TktkDX12Game/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"
#include "TktkDX12Game/GameObject/GameObjectManager.h"
#include "TktkDX12Game/GameObject/GameObject.h"


namespace tktk
{
	std::unique_ptr<SceneManager>			DX12GameManager::m_sceneManager;
	std::unique_ptr<GameObjectManager>		DX12GameManager::m_gameObjectManager;
	std::unique_ptr<ComponentManager>		DX12GameManager::m_componentManager;
	std::unique_ptr<Window>					DX12GameManager::m_window;
	std::unique_ptr<DX3DBaseObjects>		DX12GameManager::m_dx3dBaseObjects;
	std::unique_ptr<Sprite>					DX12GameManager::m_sprite;
	std::unique_ptr<BasicMesh>				DX12GameManager::m_basicMesh;
	std::unique_ptr<BasicMeshMaterial>		DX12GameManager::m_basicMeshMaterial;

	void DX12GameManager::initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath)
	{
		m_sceneManager			= std::make_unique<SceneManager>(sceneNum);
		m_gameObjectManager		= std::make_unique<GameObjectManager>();
		m_componentManager		= std::make_unique<ComponentManager>();
		m_window				= std::make_unique<Window>(windowInitParam);
		m_dx3dBaseObjects		= std::make_unique<DX3DBaseObjects>(dx3dInitParam, m_window->getHWND(), windowInitParam.windowSize, tktkMath::colorBlue);

		tktk::ShaderFilePaths spriteShaderFilePaths{};
		spriteShaderFilePaths.vsFilePath = tktkLibResFolderPath + "TktkLibRes/shader/SpriteVertexShader.cso";
		spriteShaderFilePaths.psFilePath = tktkLibResFolderPath + "TktkLibRes/shader/SpritePixelShader.cso";
		m_sprite = std::make_unique<Sprite>(spriteShaderFilePaths, dx3dInitParam.spriteNum);

		m_basicMesh = std::make_unique<BasicMesh>(dx3dInitParam.basicMeshNum);

		tktk::ShaderFilePaths basicMeshShaderFilePaths{};
		basicMeshShaderFilePaths.vsFilePath = tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshVertexShader.cso";
		basicMeshShaderFilePaths.psFilePath = tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshPixelShader.cso";
		m_basicMeshMaterial = std::make_unique<BasicMeshMaterial>(basicMeshShaderFilePaths, dx3dInitParam.basicMeshMaterialNum);
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

					// ˆ—‚©‚Á”ò‚Î‚µ
					canRunDX12Func = false;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (canRunDX12Func)
			{
				m_sceneManager->update();
				m_gameObjectManager->update();
				m_componentManager->update();
				m_dx3dBaseObjects->beginDraw();
				m_componentManager->draw();
				m_dx3dBaseObjects->endDraw();
			}
		}
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

	void DX12GameManager::setBackBufferRenderTarget()
	{
		m_dx3dBaseObjects->setBackBufferRenderTarget();
	}

	void DX12GameManager::setUseDepthStencilBackBufferRenderTarget(unsigned int depthStencilViewId)
	{
		m_dx3dBaseObjects->setUseDepthStencilBackBufferRenderTarget(depthStencilViewId);
	}

	void DX12GameManager::setViewport(unsigned int id)
	{
		m_dx3dBaseObjects->setViewport(id);
	}

	void DX12GameManager::setScissorRect(unsigned int id)
	{
		m_dx3dBaseObjects->setScissorRect(id);
	}

	void DX12GameManager::setGraphicsPipeLineState(unsigned int id)
	{
		m_dx3dBaseObjects->setGraphicsPipeLineState(id);
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

	void DX12GameManager::createGraphicsPipeLineState(unsigned int graphicsPipeLineId, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId)
	{
		m_dx3dBaseObjects->createGraphicsPipeLineState(graphicsPipeLineId, initParam, shaderFilePath, useRootSignatureId);
	}

	void DX12GameManager::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dx3dBaseObjects->createIndexBuffer(id, indices);
	}

	void DX12GameManager::createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize)
	{
		m_dx3dBaseObjects->createDepthStencilBuffer(id, depthStencilSize);
	}

	void DX12GameManager::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createBasicDescriptorHeap(id, initParam);
	}

	void DX12GameManager::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createDsvDescriptorHeap(id, initParam);
	}

	void DX12GameManager::gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_dx3dBaseObjects->gpuPriorityLoadTextureBuffer(id, formatParam, texDataPath);
	}

	const tktkMath::Vector3& DX12GameManager::getTextureSize(unsigned int id)
	{
		return m_dx3dBaseObjects->getTextureSize(id);
	}

	void DX12GameManager::gpuPriorityLoadPng(unsigned int id, const std::string& texDataPath)
	{
		tktk::TexBufFormatParam formatParam{};
		formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		formatParam.arraySize = 1U;
		formatParam.mipLevels = 1U;
		formatParam.sampleDescCount = 1U;
		formatParam.sampleDescQuality = 0U;

		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(id, formatParam, texDataPath);
	}

	void DX12GameManager::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_sprite->createSpriteMaterial(id, initParam);
	}

	void DX12GameManager::drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix)
	{
		m_sprite->drawSprite(id, worldMatrix);
	}

	void DX12GameManager::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_basicMesh->craete(id, initParam);
	}

	void DX12GameManager::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initparam)
	{
		m_basicMeshMaterial->create(id, initparam);
	}

	void DX12GameManager::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_basicMesh->drawMesh(id, baseArgs);
	}

	void DX12GameManager::drawBasicMeshMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		m_basicMeshMaterial->drawUseMaterial(id, baseArgs, materialArgs);
	}

	void DX12GameManager::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		BasicMeshPmdLoader::loadPmd(args);
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
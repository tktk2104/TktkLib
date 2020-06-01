#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Wrapper/Graphics/Window/WindowInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/RootSignature/RootSignatureInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/BasicDescriptorHeap/BasicDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/DsvDescriptorHeap/DsvDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/TextureBuffer/TextureBufferInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/_SystemResourceIdGetter/SystemResourceType.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/DescriptorHeapParam.h>
#include "../Scene/SceneManager.h"
#include "../GameObject/GameObjectPtr.h"
#include "../Component/ComponentManager.h"
#include "../Sprite/SpriteMaterialInitParam.h"
#include "../Mesh/MeshDrawFuncBaseArgs.h"
#include "../Mesh/MeshMaterialDrawFuncArgs.h"
#include "../Mesh/BasicMesh/Mesh/BasicMeshInitParam.h"
#include "../Mesh/BasicMesh/Material/BasicMeshMaterialInitParam.h"
#include "../Mesh/BasicMesh/Loader/BasicMeshLoadPmdArgs.h"

namespace tktk
{
	class GameObjectManager;
	class Window;
	class DX3DBaseObjects;
	class Sprite;
	class BasicMesh;
	class BasicMeshMaterial;

	class DX12GameManager
	{
	public: /* このマネージャー自体の処理 */

		static void initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath = "");
		static void run();

	public: /* ウィンドウの処理 */

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	public: /* シーンの処理 */

		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args... constructorArgs);

		static void enableScene(unsigned int id);

		static void disableScene(unsigned int id);

	public: /* ゲームオブジェクトの処理 */

		static GameObjectPtr createGameObject();
		
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		static std::forward_list<GameObjectPtr> findGameObjectWithTags(int tag);

	public: /* コンポーネントの処理 */

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		static void addCollisionGroup(int firstGroup, int secondGroup);

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args... args);

	public: /* 直接DX12の処理を呼ぶ */

		// コマンドリストを手動で実行する
		static void executeCommandList();

		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		static void setRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void setBackBuffer();

		static void setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId);

		static void setViewport(unsigned int id);

		static void setScissorRect(unsigned int id);

		static void setPipeLineState(unsigned int id);

		static void setVertexBuffer(unsigned int id);

		static void setIndexBuffer(unsigned int id);

		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		static void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

	public: /* 直接DX12のリソースを作る */

		// ルートシグネチャを作る
		static void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// パイプラインステートを作る
		static void createPipeLineState(unsigned int graphicsPipeLineId, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		template <class VertexData>
		static void createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		// インデックスバッファを作る
		static void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		template <class ConstantBufferDataType>
		static void createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// 深度ステンシルバッファを作る
		static void createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize);

		// ディスクリプタヒープを作る
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// 深度ステンシルディスクリプタヒープを作る
		static void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// GPU側優先処理でテクスチャを作る（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		//static void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// GPU側優先処理でテクスチャをロードする（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		
	public: /* 直接DX12のリソースを設定、取得する */

		template <class ConstantBufferDataType>
		static void updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		static const tktkMath::Vector3& getTextureSize(unsigned int id);

	public: /* リソース読み込み処理 */

		// GPU側優先処理でpng画像をロードする（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityLoadPng(unsigned int id, const std::string& texDataPath);

	public: /* スプライト関係の処理 */

		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		static void drawSprite(unsigned int id, const tktkMath::Matrix3& worldMatrix);

	public: /* メッシュ関係の処理 */

		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initparam);

		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		static void drawBasicMeshMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs);

		static void loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* デフォルトのリソースを使うためのIDを取得する */

		static unsigned int getSystemId(SystemViewportType type);
		static unsigned int getSystemId(SystemScissorRectType type);
		static unsigned int getSystemId(SystemVertexBufferType type);
		static unsigned int getSystemId(SystemIndexBufferType type);
		static unsigned int getSystemId(SystemConstantBufferType type);
		static unsigned int getSystemId(SystemDepthStencilBufferType type);
		static unsigned int getSystemId(SystemRootSignatureType type);
		static unsigned int getSystemId(SystemPipeLineStateType type);

	private: /* 裏実装 */

		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void updateConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	private:

		static std::unique_ptr<SceneManager>		m_sceneManager;
		static std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		static std::unique_ptr<ComponentManager>	m_componentManager;
		static std::unique_ptr<Window>				m_window;
		static std::unique_ptr<DX3DBaseObjects>		m_dx3dBaseObjects;
		static std::unique_ptr<Sprite>				m_sprite;
		static std::unique_ptr<BasicMesh>			m_basicMesh;
		static std::unique_ptr<BasicMeshMaterial>	m_basicMeshMaterial;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneManager->addScene<SceneType>(id, constructorArgs...);
	}

	template<class ComponentType>
	inline void DX12GameManager::addUpdatePriority(float priority)
	{
		m_componentManager->addUpdatePriority<ComponentType>(priority);
	}

	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> DX12GameManager::createComponent(Args ...args)
	{
		return m_componentManager->createComponent<ComponentType>(args...);
	}

	template<class VertexData>
	inline void DX12GameManager::createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray)
	{
		createVertexBufferImpl(id, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	template<class ConstantBufferDataType>
	inline void DX12GameManager::createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		createConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	template<class ConstantBufferDataType>
	inline void DX12GameManager::updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		updateConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}
}
#endif // !DX12_GAME_MANAGER_H_
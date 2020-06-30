#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../Scene/SceneManager.h"
#include "../GameObject/GameObjectPtr.h"
#include "../Component/ComponentManager.h"
#include "DX12GameManagerUseInitParams.h"
#include "DX12GameManagerFuncInOutValueType.h"

namespace tktk
{
	class GameObjectManager;
	class Window;
	class DX3DBaseObjects;
	class DXGameResource;
	class SoundPlayer;
	class Mouse;
	class DirectInputWrapper;

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

		static void unSetRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void unSetDepthStencil(unsigned int dsvDescriptorHeapId);

		static void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void setOnlyDepthStencil(unsigned int dsvDescriptorHeapId);

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

		// レンダーターゲットバッファを作る
		static void createRenderTargetBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作る
		static void createDepthStencilBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// ディスクリプタヒープを作る
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		static void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルディスクリプタヒープを作る
		static void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// CPU側優先処理でテクスチャを作る
		static void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// GPU側優先処理でテクスチャを作る（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// CPU側優先処理でテクスチャをロードする
		static void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// GPU側優先処理でテクスチャをロードする（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);
		
	public: /* 直接DX12のリソースを設定、取得する */

		template <class ConstantBufferDataType>
		static void updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		static void clearRenderTarget(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		static const tktkMath::Vector3& getTextureSize(unsigned int id);
		static const tktkMath::Vector2& getDepthStencilSize(unsigned int id);
		static const tktkMath::Vector2& getRenderTargetSize(unsigned int id);

	public: /* スプライト関係の処理 */

		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		static void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		static void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		static void setMaterialData(unsigned int id);

		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		static void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		static void updateBoneMatrixCbuffer(unsigned int id);

	public: /* モーション関係の処理 */

		static void loadMotion(unsigned int id, const std::string& motionFileName);

		static void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* ポストエフェクト関係の処理 */

		static void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		static void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	public: /* サウンド関係の処理 */

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		static void loadSound(unsigned int id, const std::string& fileName);

		// 指定したサウンドを再生する
		static void playSound(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		static void stopSound(unsigned int id);

		// 指定したサウンドを一時停止する
		static void pauseSound(unsigned int id);

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	public: /* マウス入力関係の処理 */

		// 指定のボタンが押されているか
		static bool isPush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	public: /* キーボード入力関係の処理 */

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	public: /* ゲームパッド入力関係の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType btnType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType btnType);

	public: /* デフォルトのリソースを使うためのIDを取得する */

		static unsigned int getSystemId(SystemViewportType type);
		static unsigned int getSystemId(SystemScissorRectType type);
		static unsigned int getSystemId(SystemVertexBufferType type);
		static unsigned int getSystemId(SystemIndexBufferType type);
		static unsigned int getSystemId(SystemConstantBufferType type);
		static unsigned int getSystemId(SystemTextureBufferType type);
		static unsigned int getSystemId(SystemDepthStencilBufferType type);
		static unsigned int getSystemId(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemId(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemId(SystemDsvDescriptorHeapType type);
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
		static std::unique_ptr<DXGameResource>		m_dxGameResource;
		static std::unique_ptr<SoundPlayer>			m_soundPlayer;
		static std::unique_ptr<Mouse>				m_mouse;
		static std::unique_ptr<DirectInputWrapper>	m_directInputWrapper;
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
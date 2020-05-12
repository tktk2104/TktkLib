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
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/Transform2D/Transform2D.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/SpriteDrawer/SpriteDrawer.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/Transform3D/Transform3D.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawer.h>

struct TestScene
{
	void start()
	{

	}

	void end()
	{
		
	}

	void update()
	{

	}
};

struct VertexData
{
	tktkMath::Vector3 pos;
	tktkMath::Vector2 uv;
};

struct Player
	: public tktk::ComponentBase
{
public:

	Player()
		: tktk::ComponentBase(0.0f, 1)
	{

	}

public:

	void awake()
	{

	}

	void onEnable()
	{

	}

	void onDisable()
	{
		//setActive(true);
	}

	void onDestroy()
	{

	}

	void update()
	{
		//setActive(false);
		//destroy();
	}

	void afterCollide()
	{

	}

	bool isCollide(const tktk::ComponentBasePtr& other)
	{
		return true;
	}

	void onCollisionEnter(const tktk::GameObjectPtr& other)
	{

	}

	void onCollisionStay(const tktk::GameObjectPtr& other)
	{

	}

	void onCollisionExit(const tktk::GameObjectPtr& other)
	{

	}
};

struct Enemy
	: public tktk::ComponentBase
{
public:

	Enemy()
		: tktk::ComponentBase(0.0f, 2)
	{

	}

public:

	void update()
	{

	}

	bool isCollide(const tktk::ComponentBasePtr& other)
	{
		return true;
	}

	void onCollisionEnter(const tktk::GameObjectPtr& other)
	{

	}

	void onCollisionStay(const tktk::GameObjectPtr& other)
	{

	}

	void onCollisionExit(const tktk::GameObjectPtr& other)
	{

	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	// 「DX12GameManager」の初期設定をする
	{
		tktk::DX3DBaseObjectsInitParam initParam{};
		initParam.viewPortNum				= 1U;
		initParam.scissorRectNum			= 1U;
		initParam.vertexBufferNum			= 3U;
		initParam.indexBufferNum			= 3U;
		initParam.graphicsPipeLineNum		= 4U;//3U;
		initParam.rootSignatureNum			= 4U;//3U;
		initParam.basicDescriptorHeapNum	= 3U;
		initParam.rtvDescriptorHeapNum		= 2U;
		initParam.textureBufferNum			= 2U;
		initParam.constantBufferNum			= 3U;
		initParam.renderTargetBufferNum		= 0U;
		initParam.backBufferNum				= 2U;
		initParam.spriteNum					= 2U;
		initParam.basicMeshNum				= 2U;
		initParam.basicMeshMaterialNum		= 2U;

		tktk::DX12GameManager::initialize(1U, initParam, { hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } });
	}

	// タイトルシーンを追加する
	tktk::DX12GameManager::addScene<TestScene>(0U);

	// タイトルシーンを有効にする
	tktk::DX12GameManager::enableScene(0U);

	// テクスチャを読み込む
	{
		tktk::DX12GameManager::gpuPriorityLoadPng(0U, "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// スプライトのマテリアルを作る
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId = 1U;
		initParam.useTextureId = 0U;

		tktk::DX12GameManager::createSpriteMaterial(0U, initParam);
	}

	// メッシュをロードする
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.m_filePath = "res/Model/初音ミク.pmd";
		loadArgs.createDescriptorHeapId = 2U;
		loadArgs.createVertexBufferId = 2U;
		loadArgs.createIndexBufferId = 2U;
		loadArgs.createBasicMeshId = 0U;
		loadArgs.createBasicMeshMaterialId = 0U;

		tktk::DX12GameManager::loadPmd(loadArgs);
	}

	// テスト
	{
		tktk::DX12GameManager::addUpdatePriority<Player>(2.0f);
		tktk::DX12GameManager::addUpdatePriority<Enemy>(2.0f);
	
		tktk::DX12GameManager::addCollisionGroup(1, 2);
	
		auto player = tktk::DX12GameManager::createGameObject();
		player->createComponent<Player>();
		player->createComponent<tktk::Transform2D>(
			tktkMath::Vector2(100.0f, 100.0f),
			tktkMath::vec2One,
			45.0f,
			tktk::TraceParentType::trace_All
			);
		player->createComponent<tktk::SpriteDrawer>(
			0.0f,
			0
			);
	
		auto enemy = tktk::DX12GameManager::createGameObject();
		enemy->createComponent<Enemy>();

		auto miku = tktk::DX12GameManager::createGameObject();
		miku->createComponent<tktk::Transform3D>(
			tktkMath::vec3Zero,
			tktkMath::vec3One,
			tktkMath::quaternionIdentity,
			tktk::TraceParentType::trace_All
			);
		miku->createComponent<tktk::BasicMeshDrawer>(
			0.0f,
			0U
			);
	}

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}
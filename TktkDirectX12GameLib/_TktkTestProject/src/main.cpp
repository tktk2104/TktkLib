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

	{
		tktk::DX3DBaseObjectsInitParam initParam{};
		initParam.viewPortNum				= 1U;
		initParam.scissorRectNum			= 1U;
		initParam.vertexBufferNum			= 1U;
		initParam.indexBufferNum			= 1U;
		initParam.graphicsPipeLineNum		= 1U;
		initParam.rootSignatureNum			= 1U;
		initParam.basicDescriptorHeapNum	= 1U;
		initParam.rtvDescriptorHeapNum		= 1U;
		initParam.textureBufferNum			= 1U;
		initParam.constantBufferNum			= 1U;
		initParam.renderTargetBufferNum		= 0U;
		initParam.backBufferNum				= 2U;

		tktk::DX12GameManager::initialize(1U, initParam, { hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } });
	}

	tktk::DX12GameManager::addScene<TestScene>(0U);

	tktk::DX12GameManager::enableScene(0U);

	// ルートシグネチャを作る
	{
		tktk::RootSignatureInitParam initParam{};
		initParam.m_flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		initParam.m_rootParamArray.resize(2U);
		{
			initParam.m_rootParamArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.m_rootParamArray.at(0).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}
		{
			initParam.m_rootParamArray.at(1).m_shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.m_rootParamArray.at(1).m_descriptorTableArray.resize(1U);
			{
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_numDescriptors = 1;
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		initParam.m_samplerDescArray.resize(1U);
		{
			initParam.m_samplerDescArray.at(0).m_addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.m_samplerDescArray.at(0).m_bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.m_samplerDescArray.at(0).m_filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.m_samplerDescArray.at(0).m_maxLod = D3D12_FLOAT32_MAX;
			initParam.m_samplerDescArray.at(0).m_minLod = 0.0f;
			initParam.m_samplerDescArray.at(0).m_shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.m_samplerDescArray.at(0).m_comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		}

		tktk::DX12GameManager::createRootSignature(0U, initParam);
	}

	// グラフィックパイプラインを作る
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		tktk::GraphicsPipeLineStateInitParam initParam{};
		initParam.m_rasterizerDesc.MultisampleEnable = false;
		initParam.m_rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.m_rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.m_rasterizerDesc.DepthClipEnable = true;
		initParam.m_blendDesc.AlphaToCoverageEnable = false;
		initParam.m_blendDesc.IndependentBlendEnable = false;
		initParam.m_blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.m_inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.m_primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.m_renderTargetFormatArray = {
			DXGI_FORMAT_R8G8B8A8_UNORM
		};

		tktk::ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.vsFilePath = "res/BasicVertexShader.cso";
		shaderFilePaths.psFilePath = "res/BasicPixelShader.cso";

		tktk::DX12GameManager::createGraphicsPipeLineState(0U, initParam, shaderFilePaths, 0U);
	}

	// 頂点バッファを作る
	{
		std::vector<VertexData> vertices =
		{
			{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
			{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
			{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
			{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
		};
		tktk::DX12GameManager::createVertexBuffer(0U, vertices);
	}

	// インデックスバッファを作る
	{
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		tktk::DX12GameManager::createIndexBuffer(0U, indices);
	}

	// 定数バッファを作る
	{
		tktkMath::Matrix4 mat = tktkMath::mat4Identity;
		tktk::DX12GameManager::createConstantBuffer(0U, mat);
	}
	

	// テクスチャバッファを作る
	{
		tktk::TexBufFormatParam formatParam{};
		formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		formatParam.arraySize = 1U;
		formatParam.mipLevels = 1U;
		formatParam.sampleDescCount = 1U;
		formatParam.sampleDescQuality = 0U;

		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(0U, formatParam, "res/test.png");

		tktk::DX12GameManager::executeCommandList();
	}

	// ディスクリプタヒープを作る
	{
		tktk::BasicDescriptorHeapInitParam initParam{};
		initParam.m_shaderVisible = true;
		initParam.m_descriptorParamArray.resize(2U);
		initParam.m_descriptorParamArray.at(0U).m_type = tktk::BasicDescriptorType::textureBuffer;
		initParam.m_descriptorParamArray.at(0U).m_id = 0U;
		initParam.m_descriptorParamArray.at(1U).m_type = tktk::BasicDescriptorType::constantBuffer;
		initParam.m_descriptorParamArray.at(1U).m_id = 0U;

		tktk::DX12GameManager::createBasicDescriptorHeap(0U, initParam);
	}

	// テスト
	{
		tktk::DX12GameManager::addUpdatePriority<Player>(2.0f);
		tktk::DX12GameManager::addUpdatePriority<Enemy>(2.0f);

		tktk::DX12GameManager::addCollisionGroup(1, 2);

		auto player = tktk::DX12GameManager::createGameObject();
		player->createComponent<Player>();

		auto enemy = tktk::DX12GameManager::createGameObject();
		enemy->createComponent<Enemy>();

		//tktk::DX12GameManager::createComponent<Player>();
		//tktk::DX12GameManager::createComponent<Enemy>();
	}

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}
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

#include <TktkDX12Game/Component/DefaultComponents/2DComponents/PostEffectDrawer/PostEffectDrawer.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/RenderTargetClearer/RenderTargetClearer.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/ShadowMapWriter/BasicMeshShadowMapWriter.h>

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

	void start()
	{
		tra = getComponent<tktk::Transform3D>();
	}

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
		tra->addLocalRotation(tktkMath::Quaternion::createFromAxisAngle({ 0, 1, 0 }, 1.0f));

		//tra->addLocalPosition({ 1, 0, 0 });

		/*auto a = tra->calculateWorldEulerAngles();

		tra->addLocalEulerAngles({ 0.0f, 10.0f, 0.0f });*/

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

private:

	tktk::ComponentPtr<tktk::Transform3D> tra;
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
	// �uDX12GameManager�v�̏����ݒ������
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
		initParam.postEffectMaterialNum		= 1U;

		tktk::DX12GameManager::initialize(1U, initParam, { hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } });
	}

	// �^�C�g���V�[����ǉ�����
	tktk::DX12GameManager::addScene<TestScene>(0U);

	// �^�C�g���V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(0U);

	// �e�N�X�`����ǂݍ���
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(0U, "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// �X�v���C�g�̃}�e���A�������
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId = 1U;
		//initParam.srvBufferType = tktk::BufferType::texture;
		//initParam.useBufferId = 0U;
		initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDepthStencilBufferType::ShadowMap);

		tktk::DX12GameManager::createSpriteMaterial(0U, initParam);
	}

	// ���b�V�������[�h����
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.m_filePath = "res/Model/�����~�N.pmd";
		loadArgs.createDescriptorHeapIdStartNum = 2U;
		loadArgs.createVertexBufferId = 0U;
		loadArgs.createIndexBufferId = 0U;
		loadArgs.createBasicMeshId = 0U;
		loadArgs.createBasicMeshMaterialIdStartNum = 0U;
		loadArgs.loadTextureIdStartNum = 1U;

		auto result = tktk::DX12GameManager::loadPmd(loadArgs);

		if (result.createBasicMeshMaterialIdEndNum == 16U)
		{
			//throw std::runtime_error("load Pmd error");
		}
	}

	// �����_�[�^�[�Q�b�g�o�b�t�@�����
	{
		tktk::DX12GameManager::createRenderTargetBuffer(0U, tktk::DX12GameManager::getWindowSize(), tktkMath::colorRed);
	}

	// �����_�[�^�[�Q�b�g�r���[�����
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type = tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id = 0U;

		tktk::DX12GameManager::createRtvDescriptorHeap(0U, initParam);
	}

	// ���m�N���̃|�X�g�G�t�F�N�g�p�̃f�B�X�N���v�^�q�[�v�����
	{
		// �f�B�X�N���v�^�q�[�v�����
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = tktk::BasicDescriptorType::textureBuffer;

			// �����_�[�^�[�Q�b�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::renderTarget,		0U }
			};
		}
		
		tktk::DX12GameManager::createBasicDescriptorHeap(0U, descriptorHeapInitParam);
	}

	// ���m�N���̃|�X�g�G�t�F�N�g�����
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = 0U;

		tktk::DX12GameManager::createPostEffectMaterial(0U, initParam);
	}

	// �e�X�g
	{
		tktk::DX12GameManager::addUpdatePriority<Player>(2.0f);
		tktk::DX12GameManager::addUpdatePriority<Enemy>(2.0f);
	
		tktk::DX12GameManager::addCollisionGroup(1, 2);
	
		/*{
			auto player = tktk::DX12GameManager::createGameObject();
			player->createComponent<tktk::Transform2D>(
				tktkMath::Vector2(1000.0f, 520.0f),
				tktkMath::vec2One,
				0.0f,
				tktk::TraceParentType::trace_All
				);
			player->createComponent<tktk::SpriteDrawer>(
				0.0f,
				0U,
				0U
				);
		}*/

		{
			auto miku = tktk::DX12GameManager::createGameObject();
			miku->createComponent<tktk::Transform3D>(
				tktkMath::vec3Zero,
				tktkMath::vec3One,
				tktkMath::quaternionIdentity,
				tktk::TraceParentType::trace_All
				);
			miku->createComponent<tktk::BasicMeshDrawer>(
				0.0f,
				0U,
				0U
				);

			miku->createComponent<tktk::BasicMeshShadowMapWriter>(
				-10.0f,
				0U
				);

			miku->createComponent<Player>();
		}

		/*{
			auto mikuMiku = tktk::DX12GameManager::createGameObject();
			mikuMiku->createComponent<tktk::Transform3D>(
				tktkMath::Vector3(10.0f, 0.0f, 10.0f),
				tktkMath::vec3One,
				tktkMath::quaternionIdentity,
				tktk::TraceParentType::trace_All
				);
			mikuMiku->createComponent<tktk::BasicMeshDrawer>(
				0.0f,
				0U,
				0U
				);

			mikuMiku->createComponent<tktk::BasicMeshShadowMapWriter>(
				-10.0f,
				0U
				);

			mikuMiku->createComponent<Player>();
		}

		{
			auto mikuMikuMiku = tktk::DX12GameManager::createGameObject();
			mikuMikuMiku->createComponent<tktk::Transform3D>(
				tktkMath::Vector3(-10.0f, 0.0f, -10.0f),
				tktkMath::vec3One,
				tktkMath::quaternionIdentity,
				tktk::TraceParentType::trace_All
				);
			mikuMikuMiku->createComponent<tktk::BasicMeshDrawer>(
				0.0f,
				0U,
				0U
				);

			mikuMikuMiku->createComponent<tktk::BasicMeshShadowMapWriter>(
				-10.0f,
				0U
				);

			mikuMikuMiku->createComponent<Player>();
		}*/

		{
			auto postEffectObject = tktk::DX12GameManager::createGameObject();
			postEffectObject->createComponent<tktk::PostEffectDrawer>(
				1.0f,
				0U,
				tktk::DX12GameManager::getSystemId(tktk::SystemRtvDescriptorHeapType::BackBuffer)
				);
			/*postEffectObject->createComponent<tktk::RenderTargetClearer>(
				0U,
				tktkMath::colorBlack
				);*/
		}
	}

	// �v���O�����J�n
	tktk::DX12GameManager::run();

	return 0;
}
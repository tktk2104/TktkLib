#include "MainScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/Cursor.h"

#include <TktkDX12Game/Component/DefaultComponents/2DComponents/Transform2D/Transform2D.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/SpriteDrawer/SpriteDrawer.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/Transform3D/Transform3D.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawer.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/MeshAnimator/MeshAnimator.h>

#include <TktkDX12Game/Component/DefaultComponents/2DComponents/PostEffectDrawer/PostEffectDrawer.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/RenderTargetClearer/RenderTargetClearer.h>
#include <TktkDX12Game/Component/DefaultComponents/3DComponents/ShadowMapWriter/BasicMeshShadowMapWriter.h>

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
		if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Space))
		{
			tra->addLocalRotation(tktkMath::Quaternion::createFromAxisAngle({ 0, 1, 0 }, 1.0f));
		}

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

void MainScene::start()
{
	Cursor::create();

	/*tktk::DX12GameManager::playSound(0U, false);
	tktk::DX12GameManager::playSound(1U, true);*/

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
			0U,
			0U
			);

		/*miku->createComponent<tktk::BasicMeshShadowMapWriter>(
			-10.0f,
			0U,
			0U
			);*/

		miku->createComponent<tktk::MeshAnimator>(
			1U
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

void MainScene::end()
{
}

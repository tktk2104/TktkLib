#include <TktkDxlib3DWrapper/Dxlib3DLibDefinition.h>

#include <memory>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkDxlib2DWrapper/_Policy/Dxlib2DPolicy.h>
#include <TktkComponentFramework/Scene/SceneManager.h>

#include "Scene/LoadingScene/LoadingScene.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Utility/Enum/CollisionGroup.h"

#include <DxLib.h>

#include "GameObject/MeshTest/MeshTestChild/MeshTestChildScript.h"

#include <TktkMath/Vector2.h>
#include <TktkMath/Matrix3.h>

#include <string>


int main()
{

	tktk::ComponentFrameworkProcessor::addClass(
		true,
		new tktk::Dxlib2DPolicy(
			Vector2(800.0f, 600.0f),
			false//,
			//1.0f,
			//true
			));

	//tktk::ComponentFrameworkProcessor::addUpdatePriority<tktk::MeshDrawer>(-100.0f);
	//tktk::ComponentFrameworkProcessor::addUpdatePriority<MeshTestChildScript>(100.0f);

	tktk::SceneManager::createScene<LoadingScene>();
	tktk::SceneManager::createScene<TitleScene>();

	tktk::SceneManager::enableScene<LoadingScene>();

	tktk::ComponentFrameworkProcessor::addCollisionGroupPair(
		CollisionGroup::COLLISION_GROUP_PLAYER,
		CollisionGroup::COLLISION_GROUP_ENEMY
	);

	tktk::ComponentFrameworkProcessor::run();

	return 0;
}
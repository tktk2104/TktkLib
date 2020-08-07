#include "MainScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/Cursor.h"
#include "../GameObject/Miku/Miku.h"
#include "../GameObject/SphereTest/SphereTest.h"
#include "../GameObject/Camera/CameraObject.h"
#include "../GameObject/Light/PointLightObject.h"
#include "../GameObject/PostEffectObject/PostEffectObject.h"


#include "../TutorialCode/GameObject/Player/Player.h"

void MainScene::start()
{
	/*tktk::DX12GameManager::playSound(0U, false);
	tktk::DX12GameManager::playSound(1U, true);*/

	Cursor::create();

	//CameraObject::create({ 0.0f, 16.0f, -20.0f });
	//PointLightObject::create({ 60.0f, 10.0f, -60.0f });

	Player::create(tktkMath::vec3Zero);

	Miku::create(tktkMath::vec3Zero);

	SphereTest::create(tktkMath::vec3Zero);

	PostEffectObject::create();
}

void MainScene::end()
{
}

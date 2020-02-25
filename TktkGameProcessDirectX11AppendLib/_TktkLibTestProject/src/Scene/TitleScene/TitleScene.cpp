#include "TitleScene.h"

#include "GameObject/SpriteTest/SpriteTest.h"
#include "GameObject/SoundTest/SoundTest.h"
#include "GameObject/CameLightTest/CameLightTest.h"
#include "GameObject/CameraTest/CameraTest.h"
#include "GameObject/LightTest/LightTest.h"
#include "GameObject/MeshTest/MeshTest.h"
#include "GameObject/IBLTest/IBLTest.h"

void TitleScene::sceneStart()
{
	SpriteTest::create();
	//SoundTest::create();

	CameLightTest::create();

	//CameraTest::create();
	//LightTest::create();
	MeshTest::create(Vector3(0.0f, 0.0f, 0.0f));
	/*MeshTest::create(Vector3(-10.0f, 0.0f, 0.0f));
	MeshTest::create(Vector3(10.0f, 0.0f, 0.0f));
	MeshTest::create(Vector3(0.0f, 0.0f, -10.0f));
	MeshTest::create(Vector3(0.0f, 0.0f, 10.0f));*/

	
	//IBLTest::create(Vector3(5.0f, 0.0f, 0.0f));
}

void TitleScene::sceneEnd()
{
}
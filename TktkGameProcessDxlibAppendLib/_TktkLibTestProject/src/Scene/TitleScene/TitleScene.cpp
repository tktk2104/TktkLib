#include "TitleScene.h"

#include "../../GameObject/SpriteTest/SpriteTest.h"
#include "../../GameObject/RenderTargetTest/RenderTargetTest.h"
#include "../../GameObject/BloomTest/BloomTest.h"

#include "../../GameObject/LightTest/LightTest.h"
#include "../../GameObject/CameraTest/CameraTest.h"
#include "../../GameObject/StageTest/StageTest.h"
#include "../../GameObject/MeshTest/MeshTest.h"
#include "../../GameObject/Collide3DTest/Collide3DTest.h"
#include "../../GameObject/Pistol/Pistol.h"

void TitleScene::sceneStart()
{
	SpriteTest::create();
	RenderTargetTest::create();
	BloomTest::create();

	//LightTest::create();
	//CameraTest::create();

	//Pistol::create();

	//StageTest::create();
	//MeshTest::create();
	//Collide3DTest::create();
}

void TitleScene::sceneEnd()
{
}
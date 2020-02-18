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

class A
{
public:

	int a;
	int b;
};

int main()
{
	
	/*Vector2 starPos = Vector2::zero;

	Matrix3 pose
		= Matrix3::createRotation(90)
		* Matrix3::createTranslation(Vector2(10, 0))
		* Matrix3::createRotation(90)
		* Matrix3::createScale(Vector2(1.5, 1.5));

	Vector2 resultStarPos = starPos * pose;*/

	//int StageModelHandle;
	//int CharaModelHandle;
	//int ShadowMapHandle;
	//
	//// ＤＸライブラリの初期化
	//if (DxLib_Init() < 0)
	//{
	//	// エラーが発生したら終了
	//	return -1;
	//}
	//
	//// 描画先を裏画面に変更
	//SetDrawScreen(DX_SCREEN_BACK);
	//
	//// キャラクターモデルの読み込み
	//CharaModelHandle = MV1LoadModel("res/Mesh/kendo.mv1");
	//
	//// ステージモデルの読み込み
	//StageModelHandle = MV1LoadModel("res/Mesh/koutei_oct.mv1");
	//
	//// シャドウマップハンドルの作成
	//ShadowMapHandle = MakeShadowMap(2048 * 2, 2048 * 2); //1024, 1024
	//
	//// カメラの位置と向きを設定
	//SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 80.0f, 80.0f), VGet(0.000f, 0.000f, 0.000f));
	//
	//// 描画する奥行き方向の範囲を設定
	//SetCameraNearFar(40.000f, 2000.000f);
	//
	//// ライトの方向を設定
	//SetLightDirection(VGet(10.5f, -10.5f, 10.5f));
	//
	//// シャドウマップが想定するライトの方向もセット
	//SetShadowMapLightDirection(ShadowMapHandle, VGet(10.5f, -10.5f, 10.5f));
	//
	//// シャドウマップに描画する範囲を設定
	//SetShadowMapDrawArea(ShadowMapHandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));
	//
	//// メインループ
	//while (ProcessMessage() == 0)
	//{
	//	// 画面をクリア
	//	ClearDrawScreen();
	//
	//	// シャドウマップへの描画の準備
	//	ShadowMap_DrawSetup(ShadowMapHandle);
	//
	//	// シャドウマップへステージモデルの描画
	//	MV1DrawModel(StageModelHandle);
	//
	//	// シャドウマップへキャラクターモデルの描画
	//	MV1DrawModel(CharaModelHandle);
	//
	//	// シャドウマップへの描画を終了
	//	ShadowMap_DrawEnd();
	//
	//	// 描画に使用するシャドウマップを設定
	//	SetUseShadowMap(0, ShadowMapHandle);
	//
	//	// ステージモデルの描画
	//	MV1DrawModel(StageModelHandle);
	//
	//	// キャラクターモデルの描画
	//	MV1DrawModel(CharaModelHandle);
	//
	//	// 描画に使用するシャドウマップの設定を解除
	//	SetUseShadowMap(0, -1);
	//
	//	// 裏画面の内容を表画面に反映
	//	ScreenFlip();
	//}
	//
	//// シャドウマップの削除
	//DeleteShadowMap(ShadowMapHandle);
	//
	//// ステージモデルの削除
	//MV1DeleteModel(StageModelHandle);
	//
	//// キャラクターモデルの削除
	//MV1DeleteModel(CharaModelHandle);
	//
	//// ＤＸライブラリの後始末
	//DxLib_End();
	//
	//// ソフトの終了
	//return 0;

	tktk::ComponentFrameworkProcessor::addClass(
		std::make_shared<tktk::Dxlib2DPolicy>(
			Vector2(800.0f, 600.0f),
			false//,
			//1.0f,
			//true
			));

	//tktk::ComponentFrameworkProcessor::addUpdatePriority<tktk::MeshDrawer>(-100.0f);
	//tktk::ComponentFrameworkProcessor::addUpdatePriority<MeshTestChildScript>(100.0f);

	tktk::SceneManager::addScene(std::make_shared<LoadingScene>());
	tktk::SceneManager::addScene(std::make_shared<TitleScene>());

	tktk::SceneManager::enableScene<LoadingScene>();

	tktk::ComponentFrameworkProcessor::addCollisionGroupPair(
		CollisionGroup::COLLISION_GROUP_PLAYER,
		CollisionGroup::COLLISION_GROUP_ENEMY
	);

	tktk::ComponentFrameworkProcessor::run();

	return 0;
}
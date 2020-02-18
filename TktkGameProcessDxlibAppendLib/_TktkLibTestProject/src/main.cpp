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
	//// �c�w���C�u�����̏�����
	//if (DxLib_Init() < 0)
	//{
	//	// �G���[������������I��
	//	return -1;
	//}
	//
	//// �`���𗠉�ʂɕύX
	//SetDrawScreen(DX_SCREEN_BACK);
	//
	//// �L�����N�^�[���f���̓ǂݍ���
	//CharaModelHandle = MV1LoadModel("res/Mesh/kendo.mv1");
	//
	//// �X�e�[�W���f���̓ǂݍ���
	//StageModelHandle = MV1LoadModel("res/Mesh/koutei_oct.mv1");
	//
	//// �V���h�E�}�b�v�n���h���̍쐬
	//ShadowMapHandle = MakeShadowMap(2048 * 2, 2048 * 2); //1024, 1024
	//
	//// �J�����̈ʒu�ƌ�����ݒ�
	//SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 80.0f, 80.0f), VGet(0.000f, 0.000f, 0.000f));
	//
	//// �`�悷�鉜�s�������͈̔͂�ݒ�
	//SetCameraNearFar(40.000f, 2000.000f);
	//
	//// ���C�g�̕�����ݒ�
	//SetLightDirection(VGet(10.5f, -10.5f, 10.5f));
	//
	//// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	//SetShadowMapLightDirection(ShadowMapHandle, VGet(10.5f, -10.5f, 10.5f));
	//
	//// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	//SetShadowMapDrawArea(ShadowMapHandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));
	//
	//// ���C�����[�v
	//while (ProcessMessage() == 0)
	//{
	//	// ��ʂ��N���A
	//	ClearDrawScreen();
	//
	//	// �V���h�E�}�b�v�ւ̕`��̏���
	//	ShadowMap_DrawSetup(ShadowMapHandle);
	//
	//	// �V���h�E�}�b�v�փX�e�[�W���f���̕`��
	//	MV1DrawModel(StageModelHandle);
	//
	//	// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
	//	MV1DrawModel(CharaModelHandle);
	//
	//	// �V���h�E�}�b�v�ւ̕`����I��
	//	ShadowMap_DrawEnd();
	//
	//	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	//	SetUseShadowMap(0, ShadowMapHandle);
	//
	//	// �X�e�[�W���f���̕`��
	//	MV1DrawModel(StageModelHandle);
	//
	//	// �L�����N�^�[���f���̕`��
	//	MV1DrawModel(CharaModelHandle);
	//
	//	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	//	SetUseShadowMap(0, -1);
	//
	//	// ����ʂ̓��e��\��ʂɔ��f
	//	ScreenFlip();
	//}
	//
	//// �V���h�E�}�b�v�̍폜
	//DeleteShadowMap(ShadowMapHandle);
	//
	//// �X�e�[�W���f���̍폜
	//MV1DeleteModel(StageModelHandle);
	//
	//// �L�����N�^�[���f���̍폜
	//MV1DeleteModel(CharaModelHandle);
	//
	//// �c�w���C�u�����̌�n��
	//DxLib_End();
	//
	//// �\�t�g�̏I��
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
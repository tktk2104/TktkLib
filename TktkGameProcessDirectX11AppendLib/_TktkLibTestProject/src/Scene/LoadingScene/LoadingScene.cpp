#include "LoadingScene.h"

#include "../TitleScene/TitleScene.h"

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkDirectX11Wrapper/Graphics/Window/Window.h>
#include <TktkDirectX11Wrapper/Sound/Sound.h>
#include <TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h>
#include <TktkDirectX11Wrapper/Graphics/Mesh/Loader/MeshLoader.h>
#include <TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MeshConstantBufferData.h>
#include <TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonLoader.h>
#include <TktkDirectX11Wrapper/Graphics/Animation/AnimationLoader.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>

#include <TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxLoader.h>
#include "ObjectLoad/LoadPistolPbrMaterial.h"
#include "ObjectLoad/LoadPistolIblMaterial.h"
#include "ObjectLoad/LoadPistolPbrIblMaterial.h"

void LoadingScene::sceneStart()
{
	tktk::Screen::setBackgroundColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

	tktk::Sound::load(SOUND_BGM_TEST,	"res/sound/kendo.wav");
	tktk::Sound::load(SOUND_SE_TEST,	"res/sound/damage.wav");

	tktk::Texture2D::load(TEXTURE_2D_SPRITE_TEST, "res/texture/test.png");
	tktk::Texture2D::load(TEXTURE_2D_SPRITE_CUBE, "res/texture/cubemap/TestEnvHDR.dds");
	tktk::Texture2D::load(TEXTURE_2D_SPRITE_ENV, "res/texture/EnvBrdf.png");

	tktk::MeshLoader::loadMesh("res/mesh/pistol/pistol.msh", MESH_PISTOL, MATERIAL_PISTOL);
	tktk::Texture2D::load(TEXTURE_2D_SPRITE_MeSm, "res/mesh/pistol/Cerberus_Metallic_Smoothness.png");
	tktk::Texture2D::load(TEXTURE_2D_SPRITE_AmOc, "res/mesh/pistol/Cerberus_AO.png");
	LoadPistolPbrMaterial();
	LoadPistolIblMaterial();
	LoadPistolPbrIblMaterial();

	tktk::MeshLoader::loadMesh("res/mesh/Robot_Kyle/Robot_Kyle.meshs", MESH_ROBOT_KYLE, MATERIAL_ROBOT_KYLE);

	tktk::SkeletonLoader::load(SKELETON_YBot, "res/mesh/Robot_Kyle/Robot_Kyle.skls");
	tktk::AnimationLoader::load(ANIMATION_YBot_kicking_1, "res/mesh/Robot_Kyle/Y_Bot@kicking_1.anms");

	tktk::SceneManager::enableScene<TitleScene>();
	tktk::SceneManager::disableScene<LoadingScene>();
}

void LoadingScene::sceneEnd()
{
}
#include "LoadingScene.h"

#include "../TitleScene/TitleScene.h"

void LoadingScene::sceneStart()
{
	tktk::Assets2DLoader::loadTextureFile("res/Text/ResourcePaths/textureResourcePaths.txt");
	tktk::Assets2DLoader::loadSoundFile("res/Text/ResourcePaths/soundResourcePaths.txt");
	tktk::Assets2DLoader::loadPixelShaderFile("res/Text/ResourcePaths/pixelShaderResourcePaths.txt");
	//tktk::Assets3DLoader::loadMeshFile("res/Text/ResourcePaths/meshResourcePaths.txt");
	//tktk::Assets3DLoader::loadSoundFile("res/Text/ResourcePaths/sound3dResourcePaths.txt");

	tktk::Assets2DManager::getRenderTargetAssets()->createRenderTarget(
		RenderTargetId::RENDER_TARGET_BEFOR_BLOOM,
		tktk::Screen::getGameScreenSize(),
		true
	);

	tktk::Assets2DManager::getRenderTargetAssets()->createRenderTarget(
		RenderTargetId::RENDER_TARGET_BRIGHT_PASS,
		tktk::Screen::getGameScreenSize() / 4,
		true
	);

	tktk::Assets2DManager::getRenderTargetAssets()->createRenderTarget(
		RenderTargetId::RENDER_TARGET_BLUR_H,
		tktk::Screen::getGameScreenSize() / 4,
		true
	);

	tktk::Assets2DManager::getRenderTargetAssets()->createRenderTarget(
		RenderTargetId::RENDER_TARGET_BLUR_V,
		tktk::Screen::getGameScreenSize() / 4,
		true
	);

	tktk::Assets2DManager::getRenderTargetAssets()->createRenderTarget(
		RenderTargetId::RENDER_TARGET_BLOOM_COMBINE,
		tktk::Screen::getGameScreenSize(),
		true
	);

	/*tktk::Assets3DManager::getShadowMapAssets().lock()->createShadowMap(
		ShadowMapId::BASE_SHADOW_MAP,
		1024 * 4,
		1024 * 4
	);*/

	tktk::SceneManager::enableScene<TitleScene>();
	tktk::SceneManager::disableScene<LoadingScene>();
}

void LoadingScene::sceneEnd()
{
	
}
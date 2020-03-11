#include <TktkDirectX11Wrapper/DirectX11LibDefinition.h>

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h>
#include <TktkDirectX11Wrapper/_Policy/DirectX11Policy.h>
#include "Scene/LoadingScene/LoadingScene.h"
#include "Scene/TitleScene/TitleScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	tktk::ComponentFrameworkProcessor::createClass<tktk::DirectX11Policy>(
		true,
		hInstance,
		nCmdShow,
		"TestWindow",
		Vector2(1920.0f, 1080.0f),//Vector2(640.0f, 480.0f),
		false,
		"res/shader/line2DShader/Line2DPixelShader.cso",
		"res/shader/line2DShader/Line2DVertexShader.cso",
		"res/shader/spriteShader/SpritePixelShader.cso",
		"res/shader/spriteShader/SpriteVertexShader.cso",
		"res/shader/meshShader/MeshPixelShader.cso",
		"res/shader/meshShader/MeshVertexShader.cso",
		"res/shader/PbrMeshShader/PbrMeshPixelShader.cso",
		"res/shader/PbrMeshShader/PbrMeshVertexShader.cso",
		"res/shader/iblMeshShader/IblMeshPixelShader.cso",
		"res/shader/iblMeshShader/IblMeshVertexShader.cso",
		"res/shader/pbrIblMeshShader/PbrIblMeshPixelShader.cso",
		"res/shader/pbrIblMeshShader/PbrIblMeshVertexShader.cso"
	);
	
	tktk::SceneManager::createScene<LoadingScene>();
	tktk::SceneManager::createScene<TitleScene>();
	tktk::SceneManager::enableScene<LoadingScene>();
	
	tktk::ComponentFrameworkProcessor::run();
}
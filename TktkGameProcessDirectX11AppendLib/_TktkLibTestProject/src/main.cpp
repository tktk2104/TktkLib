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
		false
	);
	
	tktk::SceneManager::createScene<LoadingScene>();
	tktk::SceneManager::createScene<TitleScene>();
	tktk::SceneManager::enableScene<LoadingScene>();
	
	tktk::ComponentFrameworkProcessor::run();
}
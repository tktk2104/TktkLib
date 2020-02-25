#include <TktkDirectX11Wrapper/DirectX11LibDefinition.h>

#include <TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkDirectX11Wrapper/_Policy/DirectX11Policy.h>
#include <TktkDirectX11Wrapper/Graphics/Screen/Screen.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	tktk::ComponentFrameworkProcessor::createClass<tktk::DirectX11Policy>(
		true,
		hInstance,
		nCmdShow,
		"TestWindow",
		Vector2(640.0f, 480.0f),
		false,
		"tutorialRes/shader/SpritePixelShader.cso",
		"tutorialRes/shader/SpriteVertexShader.cso",
		"tutorialRes/shader/MeshPixelShader.cso",
		"tutorialRes/shader/MeshVertexShader.cso",
		"tutorialRes/shader/PbrMeshPixelShader.cso",
		"tutorialRes/shader/PbrMeshVertexShader.cso",
		"tutorialRes/shader/IblMeshPixelShader.cso",
		"tutorialRes/shader/IblMeshVertexShader.cso",
		"tutorialRes/shader/PbrIblMeshPixelShader.cso",
		"tutorialRes/shader/PbrIblMeshVertexShader.cso"
		);

	tktk::ComponentFrameworkProcessor::run();
}
#include <TktkMathLibDefinition.h>
#include <TktkDX12WrappingLibDefinition.h>
#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	tktk::DX12GameManager gameManager{
		{ hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } }
	};

	gameManager.run();

	return 0;
}
#include <TktkFileIoLibDefinition.h>
#include <TktkMathLibDefinition.h>
#include <TktkDX12WrappingLibDefinition.h>
#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	tktk::DX3DBaseObjectsInitParam initParam{};
	initParam.viewPortNum				= 1U;
	initParam.scissorRectNum			= 1U;
	initParam.vertexBufferNum			= 1U;
	initParam.indexBufferNum			= 1U;
	initParam.graphicsPipeLineNum		= 1U;
	initParam.rootSignatureNum			= 1U;
	initParam.basicDescriptorHeapNum	= 1U;
	initParam.rtvDescriptorHeapNum		= 1U;
	initParam.textureBufferNum			= 1U;
	initParam.constantBufferNum			= 1U;
	initParam.renderTargetBufferNum		= 0U;
	initParam.backBufferNum				= 2U;

	tktk::DX12GameManager gameManager{
		initParam,
		{ hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } }
	};

	gameManager.run();

	return 0;
}
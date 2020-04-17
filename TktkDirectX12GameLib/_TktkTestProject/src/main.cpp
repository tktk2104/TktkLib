#include <TktkFileIoLibDefinition.h>
#include <TktkMathLibDefinition.h>
#include <TktkDX12WrappingLibDefinition.h>
#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

struct VertexData
{
	tktkMath::Vector3 pos;
	tktkMath::Vector2 uv;
};

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

	tktk::DX12GameManager::initialize(initParam, { hInstance, nCmdShow, "TestProject", { 1920.0f, 1080.0f } });

	// 頂点バッファを作る
	std::vector<VertexData> vertices =
	{
		{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
		{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
		{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
		{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
	};
	tktk::DX12GameManager::createVertexBuffer(0U, vertices);

	// インデックスバッファを作る
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 1, 3
	};
	tktk::DX12GameManager::createIndexBuffer(0U, indices);

	// 定数バッファを作る
	tktkMath::Matrix4 mat = tktkMath::mat4Identity;
	tktk::DX12GameManager::createConstantBuffer(0U, mat);

	tktk::DX12GameManager::run();

	return 0;
}
#include "TktkDX12Game/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

namespace tktk
{
	void BasicMeshPmdLoader::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		lodepmd::loadData outData{};

		lodepmd::load(&outData, args.m_filePath);

		DX12GameManager::createVertexBuffer(args.createVertexBufferId, outData.vertexData);
		DX12GameManager::createIndexBuffer(args.createIndexBufferId, outData.indexData);

		{
			BasicMeshMaterialInitParam materialParam{};
			materialParam.createDescriptorHeapId = args.createDescriptorHeapId;
			materialParam.useAlbedoMapTextureId = 0U;
			materialParam.useNormalMapTextureId = 0U;
			//materialParam.materialAmbient;
			//materialParam.materialDiffuse;
			//materialParam.materialSpecular;
			//materialParam.materialEmissive;
			//materialParam.materialShiniess;

			DX12GameManager::createBasicMeshMaterial(args.createBasicMeshMaterialId, materialParam);
		}

		{
			BasicMeshInitParam meshInitParam{};
			meshInitParam.useVertexBufferId = args.createVertexBufferId;
			meshInitParam.useIndexBufferId = args.createIndexBufferId;

			meshInitParam.materialSlots.reserve(1U);
			meshInitParam.materialSlots.push_back({ args.createBasicMeshMaterialId, 0U, outData.indexData.size() });
			DX12GameManager::createBasicMesh(args.createBasicMeshId, meshInitParam);
		}
	}
}
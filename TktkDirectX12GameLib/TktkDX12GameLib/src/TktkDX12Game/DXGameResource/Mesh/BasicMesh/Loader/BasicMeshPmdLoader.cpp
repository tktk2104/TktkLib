#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

namespace tktk
{
	BasicMeshLoadPmdReturnValue BasicMeshPmdLoader::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		lodepmd::loadData outData{};

		lodepmd::load(&outData, args.m_filePath);

		DX12GameManager::createVertexBuffer(args.createVertexBufferId, outData.vertexData);
		DX12GameManager::createIndexBuffer(args.createIndexBufferId, outData.indexData);

		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferId = args.createVertexBufferId;
		meshInitParam.useIndexBufferId = args.createIndexBufferId;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		unsigned int curMaterialId = args.createBasicMeshMaterialIdStartNum;
		unsigned int curIndex = 0U;

		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			BasicMeshMaterialInitParam materialParam{};
			materialParam.createDescriptorHeapId = args.createDescriptorHeapId;
			materialParam.useAlbedoMapTextureId = DX12GameManager::getSystemId(SystemTextureBufferType::White);
			materialParam.useNormalMapTextureId = DX12GameManager::getSystemId(SystemTextureBufferType::White);
			materialParam.materialAmbient	= outData.materialData.at(i).ambient;
			materialParam.materialDiffuse	= outData.materialData.at(i).diffuse;
			materialParam.materialSpecular	= outData.materialData.at(i).speqular;
			materialParam.materialEmissive	= outData.materialData.at(i).emissive;
			materialParam.materialShiniess	= outData.materialData.at(i).shiniess;

			DX12GameManager::createBasicMeshMaterial(curMaterialId, materialParam);

			meshInitParam.materialSlots.push_back({ curMaterialId, curIndex, outData.materialData.at(i).indexCount });

			curMaterialId++;
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createBasicMesh(args.createBasicMeshId, meshInitParam);

		BasicMeshLoadPmdReturnValue returnValue{};
		returnValue.createBasicMeshMaterialIdEndNum = curMaterialId--;

		return returnValue;
	}
}
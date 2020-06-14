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
		meshInitParam.indexNum = outData.indexData.size();
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		unsigned int curDescriptorHeapId	= args.createDescriptorHeapIdStartNum;
		unsigned int curTextureId			= args.loadTextureIdStartNum;
		unsigned int curMaterialId			= args.createBasicMeshMaterialIdStartNum;
		unsigned int curIndex				= 0U;

		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			BasicMeshMaterialInitParam materialParam{};

			materialParam.createDescriptorHeapId = curDescriptorHeapId++;

			if (outData.materialData.at(i).textureFilePath != "")
			{
				DX12GameManager::cpuPriorityLoadTextureBuffer(curTextureId, outData.materialData.at(i).textureFilePath);
			}
			else
			{
				TexBufFormatParam formatParam{};
				formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
				formatParam.arraySize = 1U;
				formatParam.mipLevels = 1U;
				formatParam.sampleDescCount = 1U;
				formatParam.sampleDescQuality = 0U;

				TexBuffData dataParam{};

				for (unsigned int j = 0; j < 16; j++)
				{
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.r));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.g));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.b));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.a));
				}

				dataParam.width = 4U;
				dataParam.height = 4U;

				DX12GameManager::cpuPriorityCreateTextureBuffer(curTextureId, formatParam, dataParam);
			}
			materialParam.useNormalMapTextureId = DX12GameManager::getSystemId(SystemTextureBufferType::White);
			materialParam.materialAmbient	= { 0.3f, 1.0f };
			materialParam.materialDiffuse	= outData.materialData.at(i).diffuse;
			materialParam.materialSpecular	= outData.materialData.at(i).speqular;
			materialParam.materialEmissive	= outData.materialData.at(i).emissive;
			materialParam.materialShiniess	= outData.materialData.at(i).shiniess;
			materialParam.useAlbedoMapTextureId = curTextureId++;

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
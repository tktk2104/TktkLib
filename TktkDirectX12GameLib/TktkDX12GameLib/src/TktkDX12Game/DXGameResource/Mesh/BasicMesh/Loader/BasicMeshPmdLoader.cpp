#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	// スケルトンを作る
	inline void craeteSkeleton(unsigned int createSkeletonId, const std::vector<lodepmd::loadData::OutBone>& boneData);

	// 読み込み関数
	BasicMeshLoadPmdReturnValue BasicMeshPmdLoader::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		// pmdファイルのロード処理の出力変数
		lodepmd::loadData outData{};

		// ロードを行う
		lodepmd::load(&outData, args.filePath);

		// 頂点バッファを作る
		DX12GameManager::createVertexBuffer(args.createVertexBufferId, outData.vertexData);

		// インデックスバッファを作る
		DX12GameManager::createIndexBuffer(args.createIndexBufferId, outData.indexData);

		// 通常メッシュの作成に必要な情報
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferId = args.createVertexBufferId;
		meshInitParam.useIndexBufferId = args.createIndexBufferId;
		meshInitParam.indexNum = outData.indexData.size();
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// 連番のIDで作成するリソースの次に使用するIDの値
		unsigned int curDescriptorHeapId	= args.createDescriptorHeapIdStartNum;
		unsigned int curTextureId			= args.createTextureIdStartNum;
		unsigned int curMaterialId			= args.createBasicMeshMaterialIdStartNum;

		// 現在のインデックス（インデックスバッファの位置）
		unsigned int curIndex				= 0U;

		// マテリアルの数だけループ
		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			// マテリアルの作成に必要な情報
			BasicMeshMaterialInitParam materialParam{};

			materialParam.createDescriptorHeapId = curDescriptorHeapId;

			// マテリアルにテクスチャが設定されていたら
			if (outData.materialData.at(i).textureFilePath != "")
			{
				// テクスチャを読み込む
				DX12GameManager::cpuPriorityLoadTextureBuffer(curTextureId, outData.materialData.at(i).textureFilePath);
			}
			// テクスチャが設定されていなかったら
			else
			{
				// 最初の大きさの環境光の色のテクスチャを作成する

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

				// テクスチャが小さすぎるのでコマンドリスト
				DX12GameManager::cpuPriorityCreateTextureBuffer(curTextureId, formatParam, dataParam);
			}
			materialParam.useNormalMapTextureId = DX12GameManager::getSystemId(SystemTextureBufferType::White);
			materialParam.materialAmbient	= { 0.3f, 1.0f }; // ※マテリアルの環境光の値は定数値を設定する
			materialParam.materialDiffuse	= outData.materialData.at(i).diffuse;
			materialParam.materialSpecular	= outData.materialData.at(i).speqular;
			materialParam.materialEmissive	= outData.materialData.at(i).emissive;
			materialParam.materialShiniess	= outData.materialData.at(i).shiniess;
			materialParam.useAlbedoMapTextureId = curTextureId;

			// 通常メッシュのマテリアルを作る
			DX12GameManager::createBasicMeshMaterial(curMaterialId, materialParam);

			// 通常メッシュのサブセット情報を更新
			meshInitParam.materialSlots.push_back({ curMaterialId, curIndex, outData.materialData.at(i).indexCount });

			// 各種連番IDをインクリメント
			curDescriptorHeapId++;
			curMaterialId++;
			curTextureId++;

			// 現在のインデックスを加算
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createBasicMesh(args.createBasicMeshId, meshInitParam);

		// スケルトンを作る
		craeteSkeleton(args.createSkeletonId, outData.boneData);

		// 連番のIDで作成したリソースの最後のIDの値を返す
		return { curDescriptorHeapId--, curMaterialId--, curTextureId-- };
	}

	// スケルトンを作る
	void craeteSkeleton(unsigned int createSkeletonId, const std::vector<lodepmd::loadData::OutBone>& boneData)
	{
		// 骨情報の作成に必要な情報
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// スケルトンを作成する
		DX12GameManager::createSkeleton(createSkeletonId, skeletonInitParam);
	}
}
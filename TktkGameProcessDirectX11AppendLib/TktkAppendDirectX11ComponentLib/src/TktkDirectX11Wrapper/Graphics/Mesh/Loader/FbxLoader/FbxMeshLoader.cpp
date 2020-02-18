#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxMeshLoader.h"

#include <stdexcept>
#include <fbxsdk.h>
#include <filesystem>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"

namespace tktk
{
	inline static void fbxColorToColor(const fbxsdk::FbxDouble3 & in, Color * out)
	{
		(*out) = Color(static_cast<float>(in[0]), static_cast<float>(in[1]), static_cast<float>(in[2]), 1.0f);
	}

	inline static void fbxVector4ToVector3(const fbxsdk::FbxVector4 & in, Vector3 * out)
	{
		(*out) = Vector3(static_cast<float>(in[0]), static_cast<float>(in[1]), static_cast<float>(in[2]));
	}

	inline static void fbxVector2ToVetor2(const fbxsdk::FbxVector2 & in, Vector2 * out)
	{
		(*out) = Vector2(static_cast<float>(in[0]), static_cast<float>(in[1]));
	}

	void FbxMeshLoader::loadMesh(fbxsdk::FbxMesh* meshPtr, FbxLoadDataParam * out)
	{
		loadVertex(meshPtr, &(out->vertexDataArray));
		loadIndex(meshPtr, &(out->indexDataArray), &(out->subsetDataArray));
		loadMaterial(meshPtr, &(out->materialDataArray));
	}

	void FbxMeshLoader::loadVertex(fbxsdk::FbxMesh * meshPtr, std::vector<FbxVertexDataParam>* vertexDataArrayPtr)
	{
		int vertexNum = meshPtr->GetControlPointsCount();

		fbxsdk::FbxVector4* positions = meshPtr->GetControlPoints();

		fbxsdk::FbxArray<fbxsdk::FbxVector4> normals;
		meshPtr->GetPolygonVertexNormals(normals);

		FbxLayerElementArrayTemplate<FbxVector2>* texcoordPtr;
		meshPtr->GetTextureUV(&texcoordPtr);

		vertexDataArrayPtr->resize(static_cast<unsigned int>(vertexNum));

		for (int i = 0; i < vertexNum; ++i)
		{
			fbxVector4ToVector3(positions[i], &vertexDataArrayPtr->at(i).point);
			fbxVector4ToVector3(normals[i], &vertexDataArrayPtr->at(i).normal);
			fbxVector2ToVetor2(texcoordPtr[0][i], &vertexDataArrayPtr->at(i).texcoord);

			vertexDataArrayPtr->at(i).normal = vertexDataArrayPtr->at(i).normal.normalized();

			vertexDataArrayPtr->at(i).texcoord.y *= -1;

			Vector3::orthoNormalize(
				&vertexDataArrayPtr->at(i).normal,
				&vertexDataArrayPtr->at(i).tangent,
				&vertexDataArrayPtr->at(i).binormal
			);

			vertexDataArrayPtr->at(i).bones[0] = 0;
			vertexDataArrayPtr->at(i).bones[1] = 0;
			vertexDataArrayPtr->at(i).bones[2] = 0;
			vertexDataArrayPtr->at(i).bones[3] = 0;

			vertexDataArrayPtr->at(i).weight[0] = 1.0f;
			vertexDataArrayPtr->at(i).weight[1] = 0.0f;
			vertexDataArrayPtr->at(i).weight[2] = 0.0f;
			vertexDataArrayPtr->at(i).weight[3] = 0.0f;
		}


		int skinCount = meshPtr->GetDeformerCount(FbxDeformer::eSkin);

		for (int i = 0; i < skinCount; ++i)
		{
			FbxSkin* skin = (FbxSkin*)meshPtr->GetDeformer(i, FbxDeformer::eSkin);

			int clusterNum = skin->GetClusterCount();

			for (int j = 0; j < clusterNum; ++j)
			{
				FbxCluster* cluster = skin->GetCluster(j);

				int pointNum = cluster->GetControlPointIndicesCount();
				int* pointAry = cluster->GetControlPointIndices();
				double* weightAry = cluster->GetControlPointWeights();

				for (int k = 0; k < pointNum; ++k)
				{
					int index = 0;

					while (true)
					{
						if (vertexDataArrayPtr->at(pointAry[k]).bones[index] == 0U)
						{
							vertexDataArrayPtr->at(pointAry[k]).bones[index] = (unsigned char)weightAry[k];
							vertexDataArrayPtr->at(pointAry[k]).weight[index] = (float)weightAry[k];
							break;
						}
						index++;
					}
				}
			}
		}
	}

	void FbxMeshLoader::loadIndex(fbxsdk::FbxMesh * meshPtr, std::vector<unsigned int>* indexDataArrayPtr, std::vector<FbxSubsetDataParam>* subsetDataArrayPtr)
	{
		int polygonNum = meshPtr->GetPolygonCount();

		indexDataArrayPtr->resize(static_cast<unsigned int>(polygonNum * 3));

		unsigned int curIndex = 0U;

		for (int i = 0; i < polygonNum; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				indexDataArrayPtr->at(curIndex++) = static_cast<unsigned int>(meshPtr->GetPolygonVertex(i, j));
			}
		}

		FbxSubsetDataParam subsetdataParam;
		subsetdataParam.material = 0;
		subsetdataParam.start = 0;
		subsetdataParam.count = polygonNum * 3;

		subsetDataArrayPtr->push_back(subsetdataParam);
	}

	void FbxMeshLoader::loadMaterial(fbxsdk::FbxMesh * meshPtr, std::vector<FbxMaterialDataParam>* materialDataArrayPtr)
	{
		FbxNode* nodePtr = meshPtr->GetNode();

		if (nodePtr == 0) return;

		int materialNum = nodePtr->GetMaterialCount();

		if (materialNum == 0) return;

		materialDataArrayPtr->resize(materialNum);

		for (int i = 0; i < materialNum; ++i)
		{
			// fbxマテリアル情報を取得
			fbxsdk::FbxSurfaceMaterial* materialPtr = nodePtr->GetMaterial(i);

			if (materialPtr == 0) continue;

			if (materialPtr->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
			{
				fbxsdk::FbxSurfaceLambert* lambert = (fbxsdk::FbxSurfaceLambert*)materialPtr;
				
				fbxColorToColor(lambert->Ambient.Get(), &materialDataArrayPtr->at(i).ambient);
				fbxColorToColor(lambert->Diffuse.Get(), &materialDataArrayPtr->at(i).diffuse);
				fbxColorToColor(lambert->Emissive.Get(), &materialDataArrayPtr->at(i).emission);
			}
			else if (materialPtr->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
			{
				fbxsdk::FbxSurfacePhong* phong = (fbxsdk::FbxSurfacePhong*)materialPtr;

				fbxColorToColor(phong->Ambient.Get(), &materialDataArrayPtr->at(i).ambient);
				fbxColorToColor(phong->Diffuse.Get(), &materialDataArrayPtr->at(i).diffuse);
				fbxColorToColor(phong->Emissive.Get(), &materialDataArrayPtr->at(i).emission);
				fbxColorToColor(phong->Specular.Get(), &materialDataArrayPtr->at(i).specular);
				materialDataArrayPtr->at(i).shiniess = (float)phong->Shininess.Get();
			}

			// ディフューズテクスチャのパスをロード
			loadDiffuseTextureName(materialPtr, &materialDataArrayPtr->at(i));

			// ノーマルマップのパスをロード
			loadNormalMapTextureName(materialPtr, &materialDataArrayPtr->at(i));
		}
	}

	void FbxMeshLoader::loadDiffuseTextureName(fbxsdk::FbxSurfaceMaterial* materialPtr, FbxMaterialDataParam* materialDataPtr)
	{
		fbxsdk::FbxProperty fbxProperty = materialPtr->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);

		int textureCount = fbxProperty.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

		for (int i = 0; i < textureCount; i++)
		{
			fbxsdk::FbxFileTexture* fileTexturePtr = fbxProperty.GetSrcObject<fbxsdk::FbxFileTexture>(i);

			if (!fileTexturePtr) continue;

			unsigned int size = strlen(fileTexturePtr->GetFileName());
			memcpy(materialDataPtr->textureFileName, fileTexturePtr->GetFileName(), size);
			materialDataPtr->textureFileName[size] = '\0';
		}

		const int layeredTextureCount = fbxProperty.GetSrcObjectCount<FbxLayeredTexture>();

		for (int i = 0; i < layeredTextureCount; i++)
		{
			fbxsdk::FbxLayeredTexture* layeredTexturePtr = fbxProperty.GetSrcObject<fbxsdk::FbxLayeredTexture>(i);
			const int textureFileCount = layeredTexturePtr->GetSrcObjectCount<FbxFileTexture>();

			for (int j = 0; j < textureFileCount; j++)
			{
				fbxsdk::FbxFileTexture* fileTexturePtr = layeredTexturePtr->GetSrcObject<fbxsdk::FbxFileTexture>(i);

				if (!fileTexturePtr) continue;

				unsigned int size = strlen(fileTexturePtr->GetFileName());
				memcpy(materialDataPtr->textureFileName, fileTexturePtr->GetFileName(), size);
				materialDataPtr->textureFileName[size] = '\0';
			}
		}
	}

	void FbxMeshLoader::loadNormalMapTextureName(fbxsdk::FbxSurfaceMaterial * materialPtr, FbxMaterialDataParam * materialDataPtr)
	{
		fbxsdk::FbxProperty fbxProperty = materialPtr->FindProperty(fbxsdk::FbxSurfaceMaterial::sNormalMap);

		int textureCount = fbxProperty.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

		for (int i = 0; i < textureCount; i++)
		{
			fbxsdk::FbxFileTexture* fileTexturePtr = fbxProperty.GetSrcObject<fbxsdk::FbxFileTexture>(i);

			if (!fileTexturePtr) continue;

			unsigned int size = strlen(fileTexturePtr->GetFileName());
			memcpy(materialDataPtr->normalFileName, fileTexturePtr->GetFileName(), size);
			materialDataPtr->normalFileName[size] = '\0';
		}

		const int layeredTextureCount = fbxProperty.GetSrcObjectCount<FbxLayeredTexture>();

		for (int i = 0; i < layeredTextureCount; i++)
		{
			fbxsdk::FbxLayeredTexture* layeredTexturePtr = fbxProperty.GetSrcObject<fbxsdk::FbxLayeredTexture>(i);
			const int textureFileCount = layeredTexturePtr->GetSrcObjectCount<FbxFileTexture>();

			for (int j = 0; j < textureFileCount; j++)
			{
				fbxsdk::FbxFileTexture* fileTexturePtr = layeredTexturePtr->GetSrcObject<fbxsdk::FbxFileTexture>(i);

				if (!fileTexturePtr) continue;

				unsigned int size = strlen(fileTexturePtr->GetFileName());
				memcpy(materialDataPtr->normalFileName, fileTexturePtr->GetFileName(), size);
				materialDataPtr->normalFileName[size] = '\0';
			}
		}
	}
}
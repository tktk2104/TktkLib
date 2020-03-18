#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxLoader.h"

#include <filesystem>
#include <stdexcept>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxMeshLoader.h"

namespace tktk
{
	fbxsdk::FbxManager* FbxLoader::m_managerPtr{ nullptr };

	void FbxLoader::loadImpl(int meshId, const std::vector<int>& materialIdArray, const std::string & fileName)
	{
		fbxsdk::FbxScene* scenePtr;

		initSdkObjects(&scenePtr);

		int lFileFormat = -1;

		if (!m_managerPtr->GetIOPluginRegistry()->DetectReaderFileFormat(fileName.c_str(), lFileFormat))
		{
			lFileFormat = m_managerPtr->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");
		}

		// インポーターを作成
		fbxsdk::FbxImporter* importerPtr = fbxsdk::FbxImporter::Create(m_managerPtr, "tktkFbxImporter");

		if (!importerPtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// インポーターの初期化
		if (!importerPtr->Initialize(fileName.c_str(), -1, m_managerPtr->GetIOSettings()))
		{
			m_managerPtr->Destroy();
			importerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// シーンにインポートする
		if (!importerPtr->Import(scenePtr))
		{
			m_managerPtr->Destroy();
			importerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// インポーターを削除
		importerPtr->Destroy();

		// DirectXの座標系に設定
		if (scenePtr->GetGlobalSettings().GetAxisSystem() != fbxsdk::FbxAxisSystem::DirectX)
		{
			fbxsdk::FbxAxisSystem::DirectX.ConvertScene(scenePtr);
		}

		// 座標空間の単位をセンチメートルに設定
		if (scenePtr->GetGlobalSettings().GetSystemUnit().GetScaleFactor() != 1.0)
		{
			fbxsdk::FbxSystemUnit::cm.ConvertScene(scenePtr);
		}

		// 全てのポリゴンを3角形化
		fbxsdk::FbxGeometryConverter fbxGeometryConverter(m_managerPtr);
		fbxGeometryConverter.Triangulate(scenePtr, true);

		// 欲しい情報の型を宣言
		FbxLoadDataParam loadDataParam;

		// ルートノードを取得
		fbxsdk::FbxNode* fbxNodePtr = scenePtr->GetRootNode();

		if (!fbxNodePtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// fbxノードを走破する
		for (int i = 0; i < fbxNodePtr->GetChildCount(); i++)
		{
			runningNode(fbxNodePtr->GetChild(i), &loadDataParam);
		}

		std::experimental::filesystem::path meshPath(fileName);

		std::string texturePath;

		if (meshPath.has_parent_path())
		{
			texturePath = meshPath.parent_path().string() + "/";
		}

		// 頂点バッファを作る上で必要なパラメータ
		VertexBufferInitParams vertexBufferParams = { sizeof(FbxVertexDataParam), 0U, sizeof(FbxVertexDataParam) * loadDataParam.vertexDataArray.size(), loadDataParam.vertexDataArray.data() };
		// インデックスバッファを作る上で必要なパラメータ
		IndexBufferInitParams indexBufferParams = { loadDataParam.indexDataArray };
		// マテリアルスロットを作る上で必要なパラメータ
		MaterialSlotsInitParams materialSlotsParams;
		materialSlotsParams.subsets.reserve(loadDataParam.materialDataArray.size());

		for (unsigned int i = 0; i < loadDataParam.materialDataArray.size(); i++)
		{
			// マテリアルから読み込んだテクスチャはマテリアルIDを100倍した値に何番目のテクスチャかを足したの値の負の数のIDで管理される
			int baseMaterialTextureId = -(materialIdArray.at(i) * 100);

			// アルベドテクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 1, texturePath + loadDataParam.materialDataArray.at(i).textureFileName);

			// 法線テクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 2, texturePath + loadDataParam.materialDataArray.at(i).normalFileName);

			// マテリアルを作成
			Material::create(
				materialIdArray.at(i),
				SystemVertexShaderId::Mesh,
				SystemPixelShaderId::Mesh,
				loadDataParam.materialDataArray.at(i).ambient,
				loadDataParam.materialDataArray.at(i).diffuse,
				loadDataParam.materialDataArray.at(i).specular,
				loadDataParam.materialDataArray.at(i).emission,
				loadDataParam.materialDataArray.at(i).shiniess,
				baseMaterialTextureId - 1,
				baseMaterialTextureId - 2
			);

			materialSlotsParams.subsets.push_back({ loadDataParam.subsetDataArray.at(i).start, loadDataParam.subsetDataArray.at(i).count });
		}
		// メッシュデータを作成
		Mesh::create(meshId, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, vertexBufferParams, indexBufferParams, materialSlotsParams);
	}

	void FbxLoader::initSdkObjects(fbxsdk::FbxScene** scenePtr)
	{
		// マネージャーを作成
		m_managerPtr = fbxsdk::FbxManager::Create();

		if (!m_managerPtr) throw std::runtime_error("load fbx error");

		// IOセッティングの設定をする
		fbxsdk::FbxIOSettings* iosPtr = fbxsdk::FbxIOSettings::Create(m_managerPtr, IOSROOT);
		m_managerPtr->SetIOSettings(iosPtr);

		// シーンを作成
		(*scenePtr) = fbxsdk::FbxScene::Create(m_managerPtr, "tktkFbxScene");

		if (!*scenePtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}
	}

	void FbxLoader::runningNode(fbxsdk::FbxNode * nodePtr, FbxLoadDataParam * out)
	{
		if (nodePtr->GetNodeAttribute() != NULL)
		{
			switch (nodePtr->GetNodeAttribute()->GetAttributeType())
			{
			case fbxsdk::FbxNodeAttribute::eMesh:
				
				fbxsdk::FbxMesh* meshPtr = nodePtr->GetMesh();
				FbxMeshLoader::loadMesh(meshPtr, out);
				break;
			}
		}

		for (int i = 0; i < nodePtr->GetChildCount(); i++)
		{
			runningNode(nodePtr->GetChild(i), out);
		}
	}
}
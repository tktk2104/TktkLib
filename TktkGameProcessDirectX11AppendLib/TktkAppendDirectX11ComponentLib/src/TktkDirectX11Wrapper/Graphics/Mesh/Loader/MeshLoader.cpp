#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/MeshLoader.h"

#include <fstream>
#include <vector>
#include <cstddef>
#include <filesystem>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshVertexBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"

struct MaterialDataType
{
	Color ambient;
	Color diffuse;
	Color specular;
	Color emission;
	float shiniess;
	char textureFileName[128];
	char normalFileName[128];
	void* temp1{ nullptr };
	void* temp2{ nullptr };
};

struct SubsetDataType
{
	int material;
	int start;
	int count;
};

namespace tktk
{
	void MeshLoader::loadMeshImpl(int meshId, const std::vector<int> & materialIdArray, const std::string & fileName)
	{
		std::ifstream file(fileName, std::ios::binary);

		if (!file)
		{
			throw std::runtime_error("can not open" + fileName);
		}

		std::vector<MaterialDataType> materials;
		{
			unsigned int materialSize = 0;
			file.read(reinterpret_cast<char*>(&materialSize), sizeof(materialSize));
			materials.resize(materialSize);
			file.read(reinterpret_cast<char*>(materials.data()), (sizeof(MaterialDataType)) * materialSize);
		}

		std::vector<SubsetDataType> subsets;
		{
			unsigned int subsetSize = 0;
			file.read(reinterpret_cast<char*>(&subsetSize), sizeof(subsetSize));
			subsets.resize(subsetSize);
			file.read(reinterpret_cast<char*>(subsets.data()), sizeof(SubsetDataType) * subsetSize);
		}

		std::vector<unsigned int> indices;
		{
			unsigned int indicesSize = 0;
			file.read(reinterpret_cast<char*>(&indicesSize), sizeof(indicesSize));
			indices.resize(indicesSize);
			file.read(reinterpret_cast<char*>(indices.data()), sizeof(unsigned int) * indicesSize);
		}

		std::vector<MeshVertexBufferData> vertices;
		{
			unsigned int verticesSize = 0;
			file.read(reinterpret_cast<char*>(&verticesSize), sizeof(verticesSize));
			vertices.resize(verticesSize);
			file.read(reinterpret_cast<char*>(vertices.data()), sizeof(MeshVertexBufferData) * verticesSize);
		}

		std::experimental::filesystem::path meshPath(fileName);

		std::string texturePath;

		if (meshPath.has_parent_path())
		{
			texturePath = meshPath.parent_path().string() + "/";
		}

		// 頂点バッファを作る上で必要なパラメータ
		VertexBufferInitParams vertexBufferParams = { sizeof(MeshVertexBufferData), 0U, sizeof(MeshVertexBufferData) * vertices.size(), vertices.data() };
		// インデックスバッファを作る上で必要なパラメータ
		IndexBufferInitParams indexBufferParams = { indices };
		// マテリアルスロットを作る上で必要なパラメータ
		MaterialSlotsInitParams materialSlotsParams;
		materialSlotsParams.subsets.reserve(materials.size());

		for (unsigned int i = 0; i < materials.size(); i++)
		{
			// マテリアルから読み込んだテクスチャはマテリアルIDを100倍した値に何番目のテクスチャかを足したの値の負の数のIDで管理される
			int baseMaterialTextureId = -(materialIdArray.at(i) * 100) ;

			// アルベドテクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 1, texturePath + materials.at(i).textureFileName);

			// 法線テクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 2, texturePath + materials.at(i).normalFileName);

			// マテリアルを作成
			Material::create(
				materialIdArray.at(i),
				SystemVertexShaderId::Mesh,
				SystemPixelShaderId::Mesh,
				materials.at(i).ambient,
				materials.at(i).diffuse,
				materials.at(i).specular,
				materials.at(i).emission,
				materials.at(i).shiniess,
				baseMaterialTextureId - 1,
				baseMaterialTextureId - 2
			);

			materialSlotsParams.subsets.push_back({ subsets.at(i).start, subsets.at(i).count });
		}

		// メッシュデータを作成
		Mesh::create(meshId, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, vertexBufferParams, indexBufferParams, materialSlotsParams);
	}
}
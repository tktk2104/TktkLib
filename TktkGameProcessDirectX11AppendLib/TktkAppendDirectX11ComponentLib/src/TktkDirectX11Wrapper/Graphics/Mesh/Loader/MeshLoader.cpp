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
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"

struct VertexDataType
{
	Vector3 point;
	Vector3 normal;
	Vector2 texcoord;
	unsigned char bones[4];
	float weight[4];
	Vector3 tangent;
	Vector3 binormal;
};

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
	void MeshLoader::loadMesh(int meshId, const std::vector<int> & materialIdArray, const std::string & fileName)
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

		std::vector<VertexDataType> vertices;
		{
			unsigned int verticesSize = 0;
			file.read(reinterpret_cast<char*>(&verticesSize), sizeof(verticesSize));
			vertices.resize(verticesSize);
			file.read(reinterpret_cast<char*>(vertices.data()), sizeof(VertexDataType) * verticesSize);
		}

		std::experimental::filesystem::path meshPath(fileName);

		std::string texturePath;

		if (meshPath.has_parent_path())
		{
			texturePath = meshPath.parent_path().string() + "/";
		}

		for (unsigned int i = 0; i < materials.size(); i++)
		{
			// マテリアルから読み込んだテクスチャはマテリアルIDを100倍した値に何番目のテクスチャかを足したの値の負の数のIDで管理される
			int baseMaterialTextureId = -(materialIdArray.at(i) * 100) ;

			// アルベドテクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 1, texturePath + materials.at(i).textureFileName);

			// 法線テクスチャをロードする
			Texture2DManager::load(baseMaterialTextureId - 2, texturePath + materials.at(i).normalFileName);

			std::unordered_map<unsigned int, int> useTextureIdMap;
			useTextureIdMap.insert(std::make_pair(0U, baseMaterialTextureId - 1));
			useTextureIdMap.insert(std::make_pair(1U, baseMaterialTextureId - 2));

			// マテリアルを作成
			Material::create(
				materialIdArray.at(i),
				subsets.at(i).start,
				subsets.at(i).count,
				tktk::SYSTEM_VERTEX_SHADER_MESH,
				tktk::SYSTEM_PIXEL_SHADER_MESH,
				useTextureIdMap,
				materials.at(i).ambient,
				materials.at(i).diffuse,
				materials.at(i).specular,
				materials.at(i).emission,
				materials.at(i).shiniess
			);
		}

		// 頂点バッファを作る上で必要なパラメータ
		VertexBufferInitParams vertexBufferParams = { sizeof(VertexDataType), 0U, sizeof(VertexDataType) * vertices.size(), vertices.data() };

		// インデックスバッファを作る上で必要なパラメータ
		IndexBufferInitParams indexBufferParams = { indices };

		// メッシュデータを作成
		Mesh::create(meshId, vertexBufferParams, indexBufferParams);
	}
}
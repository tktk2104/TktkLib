#ifndef MESH_LOADER_H_
#define MESH_LOADER_H_

#include <string>
#include <vector>

namespace tktk
{
	// メッシュを読み込む補助クラス
	class MeshLoader
	{
	public:

		// 以下の形式で整列しているバイナリデータの読み込み専用
		/*
		unsigned int materialSize
		{
			Color ambient
			Color diffuse
			Color specular
			Color emission
			float shiniess
			char textureFileName[128]
			char normalFileName[128]
		} 
		* materialSize
		
		unsigned int subsetSize
		{
			int material
			int start
			int count
		}
		* subsetSize

		unsigned int indicesSize
		{
			int index
		}
		* indicesSize

		unsigned int verticesSize
		{
			Vector3 point
			Vector3 normal
			Vector2 texcoord
			unsigned char bones[4]
			float weight[4]
			Vector3 tangent
			Vector3 binormal
		}
		* verticesSize

		*/
		static void loadMesh(int meshId, const std::vector<int>& materialIdArray, const std::string& fileName);
	};
}
#endif // !MESH_LOADER_H_
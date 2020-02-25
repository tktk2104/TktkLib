#ifndef FBX_MESH_LOADER_H_
#define FBX_MESH_LOADER_H_

#include <fbxsdk.h>
#include "FbxLoadDataParam/FbxLoadDataParam.h"

namespace tktk
{
	class FbxMeshLoader
	{
	public:

		static void loadMesh(fbxsdk::FbxMesh* meshPtr, FbxLoadDataParam* out);

	private:

		static void loadVertex(fbxsdk::FbxMesh* meshPtr, std::vector<FbxVertexDataParam>* vertexDataArrayPtr);

		static void loadIndex(fbxsdk::FbxMesh* meshPtr, std::vector<unsigned int>* indexDataArrayPtr, std::vector<FbxSubsetDataParam>* subsetDataArrayPtr);

		static void loadMaterial(fbxsdk::FbxMesh* meshPtr, std::vector<FbxMaterialDataParam>* materialDataArrayPtr);

		static void loadDiffuseTextureName(fbxsdk::FbxSurfaceMaterial* materialPtr, FbxMaterialDataParam* materialDataPtr);

		static void loadNormalMapTextureName(fbxsdk::FbxSurfaceMaterial* materialPtr, FbxMaterialDataParam* materialDataPtr);
	};
}
#endif // !FBX_MESH_LOADER_H_
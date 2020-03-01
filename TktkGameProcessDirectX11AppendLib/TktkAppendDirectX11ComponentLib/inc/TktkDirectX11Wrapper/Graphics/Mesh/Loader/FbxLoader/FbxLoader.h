#ifndef FBX_LOADER_H_
#define FBX_LOADER_H_

#include <string>
#include <vector>
#include <fbxsdk.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "FbxLoadDataParam/FbxLoadDataParam.h"

namespace tktk
{
	class FbxLoader
	{
	public:

		template <class MeshIdType, class... MaterialIdTypes, std::enable_if_t<is_idType_all_v<MeshIdType, MaterialIdTypes...>>* = nullptr>
		static void load(const std::string& fileName, MeshIdType meshId, MaterialIdTypes... materialIds)
		{
			loadImpl(static_cast<int>(meshId), { static_cast<int>(materialIds)... }, fileName);
		}
		template <class MeshIdType, class... MaterialIdTypes, std::enable_if_t<!is_idType_all_v<MeshIdType, MaterialIdTypes...>>* = nullptr>
		static void loadMesh(const std::string& fileName, MeshIdType meshId, MaterialIdTypes... materialIds) { static_assert(false, "Id Fraud Type"); }

	private:

		static void loadImpl(int meshId, const std::vector<int>& materialIdArray, const std::string& fileName);

		static void initSdkObjects(fbxsdk::FbxScene** scenePtr);

		static void runningNode(fbxsdk::FbxNode* nodePtr, FbxLoadDataParam* out);

	private:

		static fbxsdk::FbxManager* m_managerPtr;
	};
}
#endif // !FBX_LOADER_H_

// V-
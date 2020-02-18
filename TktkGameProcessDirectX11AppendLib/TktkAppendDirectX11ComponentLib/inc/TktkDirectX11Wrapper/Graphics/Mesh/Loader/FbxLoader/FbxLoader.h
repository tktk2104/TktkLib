#ifndef FBX_LOADER_H_
#define FBX_LOADER_H_

#include <string>
#include <vector>
#include <fbxsdk.h>
#include "FbxLoadDataParam/FbxLoadDataParam.h"

namespace tktk
{
	class FbxLoader
	{
	public:

		static void load(int meshId, const std::vector<int>& materialIdArray, const std::string& fileName);

	private:

		static void initSdkObjects(fbxsdk::FbxScene** scenePtr);

		static void runningNode(fbxsdk::FbxNode* nodePtr, FbxLoadDataParam* out);

	private:

		static fbxsdk::FbxManager* m_managerPtr;
	};
}
#endif // !FBX_LOADER_H_

// V-
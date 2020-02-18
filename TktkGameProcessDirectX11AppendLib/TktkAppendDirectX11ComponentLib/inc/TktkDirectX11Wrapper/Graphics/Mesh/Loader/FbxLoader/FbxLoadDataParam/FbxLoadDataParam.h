#ifndef FBX_LOAD_DATA_PARAM_H_
#define FBX_LOAD_DATA_PARAM_H_

#include <vector>
#include "FbxVertexDataParam.h"
#include "FbxMaterialDataParam.h"
#include "FbxSubsetDataParam.h"

namespace tktk
{
	struct FbxLoadDataParam
	{
		std::vector<FbxVertexDataParam> vertexDataArray;
		std::vector<unsigned int> indexDataArray;
		std::vector<FbxMaterialDataParam> materialDataArray;
		std::vector<FbxSubsetDataParam> subsetDataArray;
	};
}
#endif // !FBX_LOAD_DATA_PARAM_H_

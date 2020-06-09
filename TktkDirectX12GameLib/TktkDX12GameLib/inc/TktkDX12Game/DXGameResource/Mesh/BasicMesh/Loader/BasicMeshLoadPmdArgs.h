#ifndef BASIC_MESH_LOAD_PMD_ARGS_H_
#define BASIC_MESH_LOAD_PMD_ARGS_H_

#include <string>

namespace tktk
{
	struct BasicMeshLoadPmdArgs
	{
		unsigned int createDescriptorHeapIdStartNum;
		unsigned int createVertexBufferId;
		unsigned int createIndexBufferId;

		unsigned int createBasicMeshId;
		unsigned int createBasicMeshMaterialIdStartNum;
		unsigned int loadTextureIdStartNum;

		std::string m_filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_ARGS_H_

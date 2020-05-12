#ifndef BASIC_MESH_PMD_LOADER_H_
#define BASIC_MESH_PMD_LOADER_H_

#include "BasicMeshLoadPmdArgs.h"

namespace tktk
{
	class BasicMeshPmdLoader
	{
	public:

		static void loadPmd(const BasicMeshLoadPmdArgs& args);
	};
}
#endif // !BASIC_MESH_PMD_LOADER_H_

#ifndef BASIC_MESH_INIT_PARAM_H_
#define BASIC_MESH_INIT_PARAM_H_

#include <vector>
#include "../Subset.h"

namespace tktk
{
	struct BasicMeshInitParam
	{
		unsigned int useVertexBufferId;
		unsigned int useIndexBufferId;
		unsigned int indexNum;
		std::vector<Subset> materialSlots;
	};
}
#endif // !BASIC_MESH_INIT_PARAM_H_
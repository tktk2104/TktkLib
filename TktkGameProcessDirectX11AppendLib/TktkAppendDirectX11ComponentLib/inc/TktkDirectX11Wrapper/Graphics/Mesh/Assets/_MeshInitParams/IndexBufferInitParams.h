#ifndef INDEX_BUFFER_INIT_PARAMS_H_
#define INDEX_BUFFER_INIT_PARAMS_H_

#include <vector>

namespace tktk
{
	struct IndexBufferInitParams
	{
		std::vector<unsigned int> indices { };
	};
}
#endif // !INDEX_BUFFER_INIT_PARAMS_H_
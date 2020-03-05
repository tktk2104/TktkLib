#ifndef MATERIAL_SLOTS_INIT_PARAMS_H_
#define MATERIAL_SLOTS_INIT_PARAMS_H_

#include <vector>
#include "../MaterialSlots/Subset.h"

namespace tktk
{
	struct MaterialSlotsInitParams
	{
		std::vector<Subset> subsets;
	};
}
#endif // !MATERIAL_SLOTS_INIT_PARAMS_H_
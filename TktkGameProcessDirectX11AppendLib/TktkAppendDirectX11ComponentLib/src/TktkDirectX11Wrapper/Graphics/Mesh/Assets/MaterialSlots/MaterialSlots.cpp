#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MaterialSlots/MaterialSlots.h"

namespace tktk
{
	MaterialSlots::MaterialSlots(const MaterialSlotsInitParams & params)
		: m_subsets(params.subsets)
	{
	}

	unsigned int MaterialSlots::getSlotsCount() const
	{
		return m_subsets.size();
	}

	const Subset & MaterialSlots::getSubset(unsigned int slotIndex) const
	{
		return m_subsets.at(slotIndex);
	}
}
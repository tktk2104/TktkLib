#include "TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/DescriptorRange/DescriptorRangeData.h"

namespace tktk
{
	void DescriptorRangeData::initialize(unsigned int numDescriptors, Type type)
	{
		m_descriptorRange.NumDescriptors = numDescriptors;
		m_descriptorRange.RangeType = static_cast<D3D12_DESCRIPTOR_RANGE_TYPE>(type);
		m_descriptorRange.BaseShaderRegister = 0;
		m_descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	}
}
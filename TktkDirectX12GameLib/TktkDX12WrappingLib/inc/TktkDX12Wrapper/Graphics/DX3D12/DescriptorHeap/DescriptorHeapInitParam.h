#ifndef DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>
#include <d3d12.h>
#include "DescriptorType.h"

namespace tktk
{
	struct DescriptorParam
	{
		DescriptorType				descriptorType;
		unsigned int				descriptorIndex;
	};

	struct DescriptorHeapInitParam
	{
		D3D12_DESCRIPTOR_HEAP_FLAGS		m_flag;
		D3D12_DESCRIPTOR_HEAP_TYPE		m_type;
		std::vector<DescriptorParam>	m_descriptorParamArray;
	};
}
#endif // !DESCRIPTOR_HEAP_INIT_PARAM_H_
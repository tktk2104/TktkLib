#ifndef RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	enum class RtvDescriptorType
	{
		normal,
		backBuffer
	};

	struct RtvDescriptorParam
	{
		RtvDescriptorType	m_type;
		unsigned int		m_id;
	};

	struct RtvDescriptorHeapInitParam
	{
		bool							m_shaderVisible{ true };
		std::vector<RtvDescriptorParam>	m_descriptorParamArray{ };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_
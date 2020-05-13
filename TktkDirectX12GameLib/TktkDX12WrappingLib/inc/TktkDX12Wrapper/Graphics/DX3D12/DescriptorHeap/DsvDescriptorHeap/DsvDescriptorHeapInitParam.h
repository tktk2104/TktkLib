#ifndef DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	enum class DsvDescriptorType
	{
		normal,
	};

	struct DsvDescriptorParam
	{
		DsvDescriptorType	m_type;
		unsigned int		m_id;
	};

	struct DsvDescriptorHeapInitParam
	{
		bool							m_shaderVisible{ true };
		std::vector<DsvDescriptorParam>	m_descriptorParamArray{ };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_
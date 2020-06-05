#ifndef BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	enum class BasicDescriptorType
	{
		constantBuffer,
		textureBuffer,
		renderTarget
	};

	struct BasicDescriptorParam
	{
		BasicDescriptorType	type;
		unsigned int		id;
	};

	struct BasicDescriptorHeapInitParam
	{
		bool								m_shaderVisible{ true };
		std::vector<BasicDescriptorParam>	m_descriptorParamArray{ };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_
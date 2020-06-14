#ifndef SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemDsvDescriptorHeapNum = 2U;

	enum class SystemDsvDescriptorHeapType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_
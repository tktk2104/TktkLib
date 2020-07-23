#ifndef SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用している通常のディスクリプタヒープの数
	constexpr unsigned int SystemBasicDescriptorHeapNum = 1U;

	// システムで使用している通常のディスクリプタヒープの種類
	enum class SystemBasicDescriptorHeapType
	{
		BasicMeshShadowMap = 0U
	};
}
#endif // !SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_
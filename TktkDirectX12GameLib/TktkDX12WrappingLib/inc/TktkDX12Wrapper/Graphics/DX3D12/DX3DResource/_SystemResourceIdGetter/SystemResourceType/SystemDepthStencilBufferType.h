#ifndef SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_
#define SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemDepthStencilBufferNum = 2U;

	enum class SystemDepthStencilBufferType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_
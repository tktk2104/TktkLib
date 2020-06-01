#ifndef SYSTEM_RESOURCE_ID_GETTER_H_
#define SYSTEM_RESOURCE_ID_GETTER_H_

#include "SystemResourceType.h"
#include "../DX3DResourceInitParam.h"

namespace tktk
{
	class SystemResourceIdGetter
	{
	public:

		SystemResourceIdGetter(const DX3DResourceInitParam& initParam);

	public:

		DX3DResourceInitParam calculateIncludingSystemResourceInitParam() const;

	public:

		unsigned int getSystemId(SystemViewportType type) const;
		unsigned int getSystemId(SystemScissorRectType type) const;
		unsigned int getSystemId(SystemVertexBufferType type) const;
		unsigned int getSystemId(SystemIndexBufferType type) const;
		unsigned int getSystemId(SystemConstantBufferType type) const;
		unsigned int getSystemId(SystemRenderTargetBufferType type) const;
		unsigned int getSystemId(SystemDepthStencilBufferType type) const;
		unsigned int getSystemId(SystemBasicDescriptorHeapType type) const;
		unsigned int getSystemId(SystemRtvDescriptorHeapType type) const;
		unsigned int getSystemId(SystemDsvDescriptorHeapType type) const;
		unsigned int getSystemId(SystemRootSignatureType type) const;
		unsigned int getSystemId(SystemPipeLineStateType type) const;

	private:

		DX3DResourceInitParam m_basicResourceNum;
	};
}
#endif // !SYSTEM_RESOURCE_ID_GETTER_H_
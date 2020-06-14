#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/_SystemResourceIdGetter/SystemResourceIdGetter.h"

namespace tktk
{
	SystemResourceIdGetter::SystemResourceIdGetter(DX3DResourceInitParam* initParam)
		: m_basicResourceNum(*initParam)
	{
		initParam->viewPortNum										+= SystemViewportNum;
		initParam->scissorRectNum									+= SystemScissorRectNum;
		initParam->bufferResourceInitParam.vertexBufferNum			+= SystemVertexBufferNum;
		initParam->bufferResourceInitParam.indexBufferNum			+= SystemIndexBufferNum;
		initParam->bufferResourceInitParam.constantBufferNum		+= SystemConstantBufferNum;
		initParam->bufferResourceInitParam.textureBufferNum			+= SystemTextureBufferNum;
		initParam->bufferResourceInitParam.renderTargetBufferNum	+= SystemRenderTargetBufferNum;
		initParam->bufferResourceInitParam.depthStencilBufferNum	+= SystemDepthStencilBufferNum;
		initParam->descriptorHeapInitParam.basicDescriptorHeapNum	+= SystemBasicDescriptorHeapNum;
		initParam->descriptorHeapInitParam.rtvDescriptorHeapNum		+= SystemRtvDescriptorHeapNum;
		initParam->descriptorHeapInitParam.dsvDescriptorHeapNum		+= SystemDsvDescriptorHeapNum;
		initParam->rootSignatureNum									+= SystemRootSignatureNum;
		initParam->pipeLineStateNum									+= SystemPipeLineStateNum;
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemViewportType type) const
	{
		return m_basicResourceNum.viewPortNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemScissorRectType type) const
	{
		return  m_basicResourceNum.scissorRectNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemVertexBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceInitParam.vertexBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemIndexBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceInitParam.indexBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemConstantBufferType type) const
	{
		return m_basicResourceNum.bufferResourceInitParam.constantBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemTextureBufferType type) const
	{
		return m_basicResourceNum.bufferResourceInitParam.textureBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRenderTargetBufferType type) const
	{
		return m_basicResourceNum.bufferResourceInitParam.renderTargetBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemDepthStencilBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceInitParam.depthStencilBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemBasicDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapInitParam.basicDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRtvDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapInitParam.rtvDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemDsvDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapInitParam.dsvDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRootSignatureType type) const
	{
		return  m_basicResourceNum.rootSignatureNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemPipeLineStateType type) const
	{
		return  m_basicResourceNum.pipeLineStateNum + static_cast<unsigned int>(type);
	}
}
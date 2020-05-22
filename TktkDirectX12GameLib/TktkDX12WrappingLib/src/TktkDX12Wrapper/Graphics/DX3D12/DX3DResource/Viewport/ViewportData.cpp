#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/Viewport/ViewportData.h"

namespace tktk
{
	void ViewportData::initialize(const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewportArray.resize(initParamArray.size());

		for (unsigned int i = 0; i < initParamArray.size(); i++)
		{
			m_viewportArray.at(i).Width		= initParamArray.at(i).windowSize.x;
			m_viewportArray.at(i).Height	= initParamArray.at(i).windowSize.y;
			m_viewportArray.at(i).TopLeftX	= initParamArray.at(i).topLeft.x;
			m_viewportArray.at(i).TopLeftY	= initParamArray.at(i).topLeft.y;
			m_viewportArray.at(i).MaxDepth	= initParamArray.at(i).maxDepth;
			m_viewportArray.at(i).MinDepth	= initParamArray.at(i).minDepth;
		}
	}

	void ViewportData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->RSSetViewports(m_viewportArray.size(), m_viewportArray.data());
	}
}
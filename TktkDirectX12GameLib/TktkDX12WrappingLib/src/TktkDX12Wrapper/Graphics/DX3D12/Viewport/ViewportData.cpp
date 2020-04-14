#include "TktkDX12Wrapper/Graphics/DX3D12/Viewport/ViewportData.h"

namespace tktk
{
	void ViewportData::initialize(const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewportArray.resize(initParamArray.size());

		for (unsigned int i = 0; i < initParamArray.size(); i++)
		{
			m_viewportArray.at(i).Width		= initParamArray.at(i).m_windowSize.x;
			m_viewportArray.at(i).Height	= initParamArray.at(i).m_windowSize.y;
			m_viewportArray.at(i).TopLeftX	= initParamArray.at(i).m_topLeft.x;
			m_viewportArray.at(i).TopLeftY	= initParamArray.at(i).m_topLeft.y;
			m_viewportArray.at(i).MaxDepth	= initParamArray.at(i).m_maxDepth;
			m_viewportArray.at(i).MinDepth	= initParamArray.at(i).m_minDepth;
		}
	}

	void ViewportData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->RSSetViewports(m_viewportArray.size(), m_viewportArray.data());
	}
}
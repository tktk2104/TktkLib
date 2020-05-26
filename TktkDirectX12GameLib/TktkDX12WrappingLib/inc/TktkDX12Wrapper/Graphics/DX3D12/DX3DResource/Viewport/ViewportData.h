#ifndef VIEWPORT_DATA_H_
#define VIEWPORT_DATA_H_

#include <vector>
#include <d3d12.h>
#undef min
#undef max
#include "ViewportInitParam.h"

namespace tktk
{
	class ViewportData
	{
	public:

		ViewportData(const std::vector<ViewportInitParam>& initParamArray);
		~ViewportData() = default;

	public:

		void set(ID3D12GraphicsCommandList* commandList) const;
	
	private:

		std::vector<D3D12_VIEWPORT> m_viewportArray{};
	};
}
#endif // !VIEWPORT_DATA_H_
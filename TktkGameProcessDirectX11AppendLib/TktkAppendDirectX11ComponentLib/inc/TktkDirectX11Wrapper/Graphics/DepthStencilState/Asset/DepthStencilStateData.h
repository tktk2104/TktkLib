#ifndef DEPTH_STENCIL_STATE_DATA_H_
#define DEPTH_STENCIL_STATE_DATA_H_

#include <d3d11.h>

namespace tktk
{
	class DepthStencilStateData
	{
	public:

		DepthStencilStateData(const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);
		~DepthStencilStateData();

		// ÉRÉsÅ[ã÷é~
		DepthStencilStateData(const DepthStencilStateData& other) = delete;
		DepthStencilStateData& operator = (const DepthStencilStateData& other) = delete;

	public:

		ID3D11DepthStencilState* getStatePtr() const;

	private:

		ID3D11DepthStencilState* m_depthStencilState{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_STATE_DATA_H_
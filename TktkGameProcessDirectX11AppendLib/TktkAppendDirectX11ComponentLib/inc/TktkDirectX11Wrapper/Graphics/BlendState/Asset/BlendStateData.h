#ifndef BLEND_STATE_DATA_H_
#define BLEND_STATE_DATA_H_

#include <d3d11.h>

namespace tktk
{
	class BlendStateData
	{
	public:

		explicit BlendStateData(const D3D11_BLEND_DESC& blendDesc);
		~BlendStateData();

		// ÉRÉsÅ[ã÷é~
		BlendStateData(const BlendStateData& other) = delete;
		BlendStateData& operator = (const BlendStateData& other) = delete;

	public:

		ID3D11BlendState* getStatePtr() const;

	private:

		ID3D11BlendState* m_blendState{ nullptr };
	};

}
#endif // !BLEND_STATE_DATA_H_
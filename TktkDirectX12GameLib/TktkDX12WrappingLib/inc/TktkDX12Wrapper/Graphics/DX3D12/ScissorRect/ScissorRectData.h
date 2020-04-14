#ifndef SCISSOR_RECT_DATA_H_
#define SCISSOR_RECT_DATA_H_

#include <vector>
#include <d3d12.h>
#undef min
#undef max
#include "ScissorRectInitParam.h"

namespace tktk
{
	class ScissorRectData
	{
	public:

		ScissorRectData() = default;
		~ScissorRectData() = default;

	public:

		void initialize(const std::vector<ScissorRectInitParam>& initParamArray);

		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<D3D12_RECT> m_scissorRectArray{};
	};
}
#endif // !SCISSOR_RECT_DATA_H_
#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <array>
#include "ViewportData.h"

namespace tktk
{
	template <int ViewportNum>
	class Viewport
	{
	public:

		Viewport() = default;

	public:

		template <int ViewportIndex>
		void create(const std::vector<ViewportInitParam>& initParamArray);

		template <int ViewportIndex>
		void set(ID3D12GraphicsCommandList* commandList);

	private:

		std::array<ViewportData, ViewportNum> m_viewportDataArray{};
	};

	template<int ViewportNum>
	template<int ViewportIndex>
	inline void Viewport<ViewportNum>::create(const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewportDataArray.at(ViewportIndex).initialize(initParamArray);
	}

	template<int ViewportNum>
	template<int ViewportIndex>
	inline void Viewport<ViewportNum>::set(ID3D12GraphicsCommandList* commandList)
	{
		m_viewportDataArray.at(ViewportIndex).set(commandList);
	}
}
#endif // !VIEWPORT_H_
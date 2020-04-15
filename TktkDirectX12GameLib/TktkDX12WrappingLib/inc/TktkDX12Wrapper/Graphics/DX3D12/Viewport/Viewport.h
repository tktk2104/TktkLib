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

		void create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		std::array<ViewportData, ViewportNum> m_viewportDataArray{};
	};

	template<int ViewportNum>
	inline void Viewport<ViewportNum>::create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewportDataArray.at(id).initialize(initParamArray);
	}

	template<int ViewportNum>
	inline void Viewport<ViewportNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_viewportDataArray.at(id).set(commandList);
	}
}
#endif // !VIEWPORT_H_
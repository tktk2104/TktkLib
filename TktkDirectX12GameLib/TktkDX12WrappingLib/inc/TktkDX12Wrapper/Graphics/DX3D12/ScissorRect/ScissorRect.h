#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <array>
#include "ScissorRectData.h"

namespace tktk
{
	template <int ScissorRectNum>
	class ScissorRect
	{
	public:

		ScissorRect() = default;

	public:

		template <int ScissorRectIndex>
		void create(const std::vector<ScissorRectInitParam>& initParamArray);

		template <int ScissorRectIndex>
		void set(ID3D12GraphicsCommandList* commandList);

	private:

		std::array<ScissorRectData, ScissorRectNum> m_scissorRectDataArray{};
	};

	template<int ScissorRectNum>
	template<int ScissorRectIndex>
	inline void ScissorRect<ScissorRectNum>::create(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRectDataArray.at(ScissorRectIndex).initialize(initParamArray);
	}

	template<int ScissorRectNum>
	template<int ScissorRectIndex>
	inline void ScissorRect<ScissorRectNum>::set(ID3D12GraphicsCommandList* commandList)
	{
		m_scissorRectDataArray.at(ScissorRectIndex).set(commandList);
	}
}
#endif // !SCISSOR_RECT_H_
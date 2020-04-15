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

		void create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		std::array<ScissorRectData, ScissorRectNum> m_scissorRectDataArray{};
	};

	template<int ScissorRectNum>
	inline void ScissorRect<ScissorRectNum>::create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRectDataArray.at(id).initialize(initParamArray);
	}

	template<int ScissorRectNum>
	inline void ScissorRect<ScissorRectNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_scissorRectDataArray.at(id).set(commandList);
	}
}
#endif // !SCISSOR_RECT_H_
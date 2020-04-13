#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include <array>
#include "PixelShaderData.h"

namespace tktk
{
	template <int PixelShaderNum>
	class PixelShader
	{
	public:

		PixelShader() = default;

	public:

		template <int PixelShaderIndex>
		void load(const std::string& fileName);

		template <int PixelShaderIndex>
		const char* getByteArrayTopPos() const;

		template <int PixelShaderIndex>
		unsigned int getByteArrayLength() const;

	private:

		std::array<PixelShaderData, PixelShaderIndex> m_pixelShaderDataMap{};
	};

	template<int PixelShaderNum>
	template<int PixelShaderIndex>
	inline void PixelShader<PixelShaderNum>::load(const std::string& fileName)
	{
		m_pixelShaderDataMap.at(PixelShaderIndex).load(fileName);
	}

	template<int PixelShaderNum>
	template<int PixelShaderIndex>
	inline const char* PixelShader<PixelShaderNum>::getByteArrayTopPos() const
	{
		return m_pixelShaderDataMap.at(PixelShaderIndex).getByteArrayTopPos();
	}

	template<int PixelShaderNum>
	template<int PixelShaderIndex>
	inline unsigned int PixelShader<PixelShaderNum>::getByteArrayLength() const
	{
		return m_pixelShaderDataMap.at(PixelShaderIndex).getByteArrayLength();
	}
}
#endif // !PIXEL_SHADER_H_
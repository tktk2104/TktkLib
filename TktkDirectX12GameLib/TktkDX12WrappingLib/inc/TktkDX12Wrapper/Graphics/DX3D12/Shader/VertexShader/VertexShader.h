#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include <array>
#include "VertexShaderData.h"

namespace tktk
{
	template <int VertexShaderNum>
	class VertexShader
	{
	public:

		VertexShader() = default;

	public:

		template <int VertexShaderIndex>
		void load(const std::string& fileName);

		template <int VertexShaderIndex>
		const char* getByteArrayTopPos() const;

		template <int VertexShaderIndex>
		unsigned int getByteArrayLength() const;

	private:

		std::array<VertexShaderData, VertexShaderNum> m_vertexShaderDataMap{};
	};

	template<int VertexShaderNum>
	template<int VertexShaderIndex>
	inline void VertexShader<VertexShaderNum>::load(const std::string& fileName)
	{
		m_vertexShaderDataMap.at(VertexShaderIndex).load(fileName);
	}

	template<int VertexShaderNum>
	template<int VertexShaderIndex>
	inline const char* VertexShader<VertexShaderNum>::getByteArrayTopPos() const
	{
		return m_vertexShaderDataMap.at(VertexShaderIndex).getByteArrayTopPos();
	}

	template<int VertexShaderNum>
	template<int VertexShaderIndex>
	inline unsigned int VertexShader<VertexShaderNum>::getByteArrayLength() const
	{
		return m_vertexShaderDataMap.at(VertexShaderIndex).getByteArrayLength();
	}
}
#endif // !VERTEX_SHADER_H_
#ifndef VERTEX_SHADER_DATA_H_
#define VERTEX_SHADER_DATA_H_

#include <string>
#include <vector>

namespace tktk
{
	class VertexShaderData
	{
	public:

		VertexShaderData() = default;
		~VertexShaderData() = default;

	public:

		void load(const std::string& fileName);

		const char* getByteArrayTopPos() const;

		unsigned int getByteArrayLength() const;

	private:

		std::vector<char> m_byteArray;
	};
}
#endif // !VERTEX_SHADER_DATA_H_

#ifndef PIXEL_SHADER_DATA_H_
#define PIXEL_SHADER_DATA_H_

#include <string>
#include <vector>

namespace tktk
{
	class PixelShaderData
	{
	public:

		PixelShaderData() = default;
		~PixelShaderData() = default;

	public:

		void load(const std::string& fileName);

		const char* getByteArrayTopPos() const;

		unsigned int getByteArrayLength() const;

	private:

		std::vector<char> m_byteArray;
	};
}
#endif // !PIXEL_SHADER_DATA_H_
#include "TktkDX12Wrapper/Graphics/DX3D12/Shader/VertexShader/VertexShaderData.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	void VertexShaderData::load(const std::string& fileName)
	{
		m_byteArray.clear();

		std::FILE* fp;

		int ret = fopen_s(&fp, fileName.c_str(), "rb");

#ifdef _DEBUG
		if (ret != 0)
		{
			throw std::runtime_error("load vertexShader error");
		}
#endif // _DEBUG

		fseek(fp, 0, SEEK_END);
		m_byteArray.resize(ftell(fp));
		fseek(fp, 0, SEEK_SET);

		fread(m_byteArray.data(), m_byteArray.size(), 1, fp);
		fclose(fp);
	}

	const char* VertexShaderData::getByteArrayTopPos() const
	{
#ifdef _DEBUG
		if (m_byteArray.empty())
		{
			throw std::runtime_error("Not Load VertexShader");
		}
#endif // _DEBUG
		return m_byteArray.data();
	}

	unsigned int VertexShaderData::getByteArrayLength() const
	{
#ifdef _DEBUG
		if (m_byteArray.empty())
		{
			throw std::runtime_error("Not Load VertexShader");
		}
#endif // _DEBUG
		return m_byteArray.size();
	}
}
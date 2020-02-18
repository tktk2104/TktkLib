#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/Texture2DAssets.h"

namespace tktk
{
	Texture2DAssets::~Texture2DAssets()
	{
		clear();
	}

	void Texture2DAssets::load(int id, const std::string & fileName)
	{
		erase(id);

		m_texture2DAssets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(fileName)
		);
	}

	void Texture2DAssets::erase(int id)
	{
		auto eraseNode = m_texture2DAssets.find(id);
		if (eraseNode == std::end(m_texture2DAssets)) return;
		m_texture2DAssets.erase(id);
	}

	void Texture2DAssets::clear()
	{
		m_texture2DAssets.clear();
	}

	const Texture2DData & Texture2DAssets::getData(int id)
	{
		return m_texture2DAssets.at(id);
	}
}
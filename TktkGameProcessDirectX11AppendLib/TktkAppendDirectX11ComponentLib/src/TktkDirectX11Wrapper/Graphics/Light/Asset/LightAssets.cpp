#include "TktkDirectX11Wrapper/Graphics/Light/Asset/LightAssets.h"

namespace tktk
{
	LightAssets::~LightAssets()
	{
		clear();
	}

	void LightAssets::create(
		int id,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Vector3 & position
	)
	{
		erase(id);

		m_lightAssets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(ambientColor, diffuseColor, specularColor, position)
		);
	}

	void LightAssets::erase(int id)
	{
		auto eraseNode = m_lightAssets.find(id);
		if (eraseNode == std::end(m_lightAssets)) return;
		m_lightAssets.erase(id);
	}

	void LightAssets::clear()
	{
		m_lightAssets.clear();
	}

	LightData * LightAssets::getLightDataPtr(int id)
	{
		return &m_lightAssets.at(id);
	}
}
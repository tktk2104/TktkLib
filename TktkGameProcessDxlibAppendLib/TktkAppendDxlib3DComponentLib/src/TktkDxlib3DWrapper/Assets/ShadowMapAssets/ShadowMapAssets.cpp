#include "TktkDxlib3DWrapper/Assets/ShadowMapAssets/ShadowMapAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void ShadowMapAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_shadowMapAssetsMap),
			std::end(m_shadowMapAssetsMap),
			[](const auto& node) { DxLib::DeleteShadowMap(node.second); }
		);
	}

	void ShadowMapAssets::createShadowMap(int id, int sizeX, int sizeY)
	{
		eraseShadowMap(id);

		int createShadowMapHandle = DxLib::MakeShadowMap(sizeX, sizeY);

		m_shadowMapAssetsMap.insert(std::make_pair(id, createShadowMapHandle));
	}

	void ShadowMapAssets::eraseShadowMap(int id)
	{
		auto eraseNode = m_shadowMapAssetsMap.find(id);
		if (eraseNode == std::end(m_shadowMapAssetsMap)) return;

		DxLib::DeleteShadowMap((*eraseNode).second);
		m_shadowMapAssetsMap.erase(id);
	}

	void ShadowMapAssets::eraseShadowMapAll()
	{
		std::for_each(
			std::begin(m_shadowMapAssetsMap),
			std::end(m_shadowMapAssetsMap),
			[](const auto& node) { DxLib::DeleteShadowMap(node.second); }
		);
		m_shadowMapAssetsMap.clear();
	}

	int ShadowMapAssets::getShadowMapHandle(int id) const
	{
		return m_shadowMapAssetsMap.at(id);
	}
}
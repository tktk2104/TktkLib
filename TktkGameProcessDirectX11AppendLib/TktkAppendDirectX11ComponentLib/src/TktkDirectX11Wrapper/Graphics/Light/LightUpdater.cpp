#include "TktkDirectX11Wrapper/Graphics/Light/LightUpdater.h"

#include <algorithm>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	LightUpdater::LightUpdater()
	{
		m_assets = ComponentFrameworkProcessor::addClass(true, new LightAssets());
	}

	LightUpdater::~LightUpdater()
	{
	}

	void LightUpdater::create(
		int id,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Vector3 & position
	)
	{
		m_assets->create(id, ambientColor, diffuseColor, specularColor, position);
	}

	void LightUpdater::erase(int id)
	{
		m_assets->erase(id);
	}

	void LightUpdater::clear()
	{
		m_assets->clear();
	}

	LightData * LightUpdater::getLightDataPtr(int id)
	{
		return m_assets->getLightDataPtr(id);
	}

	void LightUpdater::enableLight(int id)
	{
		m_enableLightIdList.insert(id);
	}

	void LightUpdater::disableLight(int id)
	{
		auto findNode = m_enableLightIdList.find(id);
		if (findNode == std::end(m_enableLightIdList)) return;
		m_enableLightIdList.erase(findNode);
	}

	void LightUpdater::disableLightAll()
	{
		m_enableLightIdList.clear();
	}

	const std::unordered_set<int>& LightUpdater::getEnableLightIdList() const
	{
		return m_enableLightIdList;
	}

	void LightUpdater::createEnableLightList(std::forward_list<LightData*>* result)
	{
		std::for_each(
			std::begin(m_enableLightIdList),
			std::end(m_enableLightIdList),
			[this, result](const auto& node) { result->push_front(getLightDataPtr(1)); }
		);
	}
}
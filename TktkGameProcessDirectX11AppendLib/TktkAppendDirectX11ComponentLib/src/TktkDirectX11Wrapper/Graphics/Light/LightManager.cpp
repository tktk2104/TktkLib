#include "TktkDirectX11Wrapper/Graphics/Light/LightManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<LightUpdater> LightManager::m_updaterPtr;

	void LightManager::setUp()
	{
		m_updaterPtr = ComponentFrameworkProcessor::addClass(true, new LightUpdater());
	}

	void LightManager::clear()
	{
		m_updaterPtr->clear();
	}

	void LightManager::disableLightAll()
	{
		m_updaterPtr->disableLightAll();
	}

	const std::unordered_set<int>& LightManager::getEnableLightIdList()
	{
		return m_updaterPtr->getEnableLightIdList();
	}

	void LightManager::createEnableLightList(std::forward_list<LightData*>* result)
	{
		return m_updaterPtr->createEnableLightList(result);
	}

	std::forward_list<LightData*> LightManager::createEnableLightList()
	{
		std::forward_list<LightData*> result;
		createEnableLightList(&result);
		return result;
	}

	void LightManager::createImpl(int id, const Color & ambientColor, const Color & diffuseColor, const Color & specularColor, const Vector3 & position)
	{
		m_updaterPtr->create(id, ambientColor, diffuseColor, specularColor, position);
	}

	void LightManager::eraseImpl(int id)
	{
		m_updaterPtr->erase(id);
	}

	LightData * LightManager::getLightDataPtrImpl(int id)
	{
		return m_updaterPtr->getLightDataPtr(id);
	}

	void LightManager::enableLightImpl(int id)
	{
		m_updaterPtr->enableLight(id);
	}

	void LightManager::disableLightImpl(int id)
	{
		m_updaterPtr->disableLight(id);
	}
}
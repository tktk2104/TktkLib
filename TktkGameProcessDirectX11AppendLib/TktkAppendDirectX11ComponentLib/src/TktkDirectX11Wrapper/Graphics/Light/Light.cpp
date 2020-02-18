#include "TktkDirectX11Wrapper/Graphics/Light/Light.h"

#include "TktkDirectX11Wrapper/Graphics/Light/LightManager.h"

namespace tktk
{
	void Light::create(
		int id,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Vector3 & position
	)
	{
		if (id <= 0)
		{
			throw std::runtime_error("LightId Fraud Value");
		}
		LightManager::create(id, ambientColor, diffuseColor, specularColor, position);
	}

	void Light::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("LightId Fraud Value");
		}
		LightManager::erase(id);
	}

	LightData * Light::getLightDataPtr(int id)
	{
		return LightManager::getLightDataPtr(id);
	}

	void Light::enableLight(int id)
	{
		LightManager::enableLight(id);
	}

	void Light::disableLight(int id)
	{
		LightManager::disableLight(id);
	}

	void Light::disableLightAll()
	{
		LightManager::disableLightAll();
	}

	const std::unordered_set<int>& Light::getEnableLightIdList()
	{
		return LightManager::getEnableLightIdList();
	}

	void Light::createEnableLightList(std::forward_list<LightData*>* result)
	{
		LightManager::createEnableLightList(result);
	}

	std::forward_list<LightData*> Light::createEnableLightList()
	{
		return LightManager::createEnableLightList();
	}
}
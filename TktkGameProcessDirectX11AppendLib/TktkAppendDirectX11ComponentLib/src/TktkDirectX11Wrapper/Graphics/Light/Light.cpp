#include "TktkDirectX11Wrapper/Graphics/Light/Light.h"

#include "TktkDirectX11Wrapper/Graphics/Light/LightManager.h"

namespace tktk
{
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

	void Light::createImpl(
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

	void Light::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("LightId Fraud Value");
		}
		LightManager::erase(id);
	}

	LightData * Light::getLightDataPtrImpl(int id)
	{
		return LightManager::getLightDataPtr(id);
	}

	void Light::enableLightImpl(int id)
	{
		LightManager::enableLight(id);
	}

	void Light::disableLightImpl(int id)
	{
		LightManager::disableLight(id);
	}
}
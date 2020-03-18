#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"

namespace tktk
{
	void Material::createImpl(int id, int useVSId, int usePSId, const Color & ambient, const Color & diffuse, const Color & specular, const Color & emission, float shiniess, const std::vector<int>& useTextureIdArray)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MaterialId Fraud Value");
		}
		MaterialManager::createImpl(id, useVSId, usePSId, ambient, diffuse, specular, emission, shiniess, useTextureIdArray);
	}

	void Material::duplicateImpl(int id, int originalId)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MaterialId Fraud Value");
		}
		MaterialManager::duplicate(id, originalId);
	}

	void Material::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MaterialId Fraud Value");
		}
		MaterialManager::erase(id);
	}

	MaterialData * Material::getDataPtrImpl(int id)
	{
		return MaterialManager::getDataPtr(id);
	}
}
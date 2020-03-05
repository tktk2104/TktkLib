#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"

namespace tktk
{
	void Material::createImpl(
		int id,
		int useVertexShaderId,
		int usePixelShaderId,
		const std::vector<int>& useTextureIdArray,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Color & emissionColor,
		float shiniess
	)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MaterialId Fraud Value");
		}
		MaterialManager::create(
			id,
			useVertexShaderId,
			usePixelShaderId,
			useTextureIdArray,
			ambientColor,
			diffuseColor,
			specularColor,
			emissionColor,
			shiniess
		);
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
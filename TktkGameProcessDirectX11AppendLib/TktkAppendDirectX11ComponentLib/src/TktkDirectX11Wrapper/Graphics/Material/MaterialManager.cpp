#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<MaterialAssets> MaterialManager::m_assetsPtr;

	void MaterialManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new MaterialAssets());
	}

	void MaterialManager::clear()
	{
		m_assetsPtr->clear();
	}

	void MaterialManager::createImpl(
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
		m_assetsPtr->create(
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

	void MaterialManager::duplicateImpl(int id, int originalId)
	{
		m_assetsPtr->duplicate(id, originalId);
	}

	void MaterialManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	MaterialData * MaterialManager::getDataPtrImpl(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}
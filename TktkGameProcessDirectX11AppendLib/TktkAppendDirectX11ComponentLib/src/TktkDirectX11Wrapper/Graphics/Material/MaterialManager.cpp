#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<MaterialAssets> MaterialManager::m_assetsPtr;

	void MaterialManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new MaterialAssets());
	}

	void MaterialManager::create(
		int id,
		int indexBufferStartPos,
		int indexBufferUseCount,
		int useVertexShaderId,
		int usePixelShaderId,
		const std::unordered_map<unsigned int, int>& useTextureIdMap,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Color & emissionColor,
		float shiniess
	)
	{
		m_assetsPtr->create(
			id,
			indexBufferStartPos,
			indexBufferUseCount,
			useVertexShaderId,
			usePixelShaderId,
			useTextureIdMap,
			ambientColor,
			diffuseColor,
			specularColor,
			emissionColor,
			shiniess
		);
	}

	void MaterialManager::duplicate(int id, int originalId)
	{
		m_assetsPtr->duplicate(id, originalId);
	}

	void MaterialManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void MaterialManager::clear()
	{
		m_assetsPtr->clear();
	}

	MaterialData * MaterialManager::getDataPtr(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}
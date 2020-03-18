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

	void MaterialManager::createImpl(int id, int useVSId, int usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, const std::vector<int>& useTextureIdArray)
	{
		m_assetsPtr->create(id, useVSId, usePSId, ambient, diffuse, specular, emission, shiniess, useTextureIdArray);
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
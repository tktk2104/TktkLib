#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<Texture2DAssets> Texture2DManager::m_assetsPtr;

	void Texture2DManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new Texture2DAssets());
	}

	void Texture2DManager::clear()
	{
		m_assetsPtr->clear();
	}

	void Texture2DManager::createImpl(int id, Texture2DBindFlag bindFlag, const std::vector<unsigned char>& textureData, unsigned int width, unsigned int height, unsigned int mipCount, unsigned int arraySize, DXGI_FORMAT format, Texture2DUsage usage, Texture2DCpuAccessFlag cpuAccessFlag, bool isCubeMap)
	{
		m_assetsPtr->create(id, bindFlag, textureData, width, height, mipCount, arraySize, format, usage, cpuAccessFlag, isCubeMap);
	}

	void Texture2DManager::loadImpl(int id, const std::string & fileName)
	{
		m_assetsPtr->load(id, fileName);
	}

	void Texture2DManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const Texture2DData & Texture2DManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}
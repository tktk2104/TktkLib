#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/MaterialLoadTextureIdManager.h"

#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/SystemTexture2DId.h"

namespace tktk
{
	int MaterialLoadTextureIdManager::m_curMaterialTexture2DId{ static_cast<int>(SystemTexture2DId::materialLoadResStart) };

	std::unordered_map<int, std::vector<int>> MaterialLoadTextureIdManager::m_materialTexture2DIdArrayMap;

	int MaterialLoadTextureIdManager::getMaterialTextureIdImpl(int materialId, unsigned int textureSlot)
	{
		if (m_materialTexture2DIdArrayMap.count(materialId) == 0)
		{
			m_materialTexture2DIdArrayMap.insert(std::make_pair(materialId, std::vector<int>()));
		}

		auto& texture2DArray = m_materialTexture2DIdArrayMap.at(materialId);

		while (texture2DArray.size() <= textureSlot)
		{
			texture2DArray.push_back(m_curMaterialTexture2DId--);
		}

		return texture2DArray.at(textureSlot);
	}
}
#include "TktkDxlib2DWrapper/Assets/TextureAssets/TextureAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void TextureAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_textureAssetsMap),
			std::end(m_textureAssetsMap),
			[](const auto& node) { node.second.unLoadTexture(); }
		);
	}

	void TextureAssets::loadTexture(int id, const std::string & assetFilePath)
	{
		eraseTexture(id);

		TextureHandles textureHandles;
		textureHandles.textureHandle = DxLib::LoadGraph(assetFilePath.c_str());

		m_textureAssetsMap.insert(std::make_pair(id, textureHandles));
	}

	void TextureAssets::loadTexture(int id, const std::string & assetFilePath, int row, int column)
	{
		eraseTexture(id);

		TextureHandles textureHandles;
		textureHandles.textureHandle = DxLib::LoadGraph(assetFilePath.c_str());

		int sizeX = 0;
		int	sizeY = 0;
		DxLib::GetGraphSize(textureHandles.textureHandle, &sizeX, &sizeY);

		int rowSize = sizeY / row;
		int columnSize = sizeX / column;

		for (int y = 0; y < sizeY; y += rowSize)
		{
			for (int x = 0; x < sizeX; x += columnSize)
			{
				int splitTextureHandle = DxLib::DerivationGraph(x, y, columnSize, rowSize, textureHandles.textureHandle);
				textureHandles.splitTextureHandles.push_back(splitTextureHandle);
			}
		}
		m_textureAssetsMap.insert(std::make_pair(id, textureHandles));
	}

	void TextureAssets::eraseTexture(int id)
	{
		auto eraseNode = m_textureAssetsMap.find(id);
		if (eraseNode == std::end(m_textureAssetsMap)) return;

		(*eraseNode).second.unLoadTexture();
		m_textureAssetsMap.erase(id);
	}

	void TextureAssets::eraseTextureAll()
	{
		std::for_each(
			std::begin(m_textureAssetsMap),
			std::end(m_textureAssetsMap),
			[](const auto& node) { node.second.unLoadTexture(); }
		);
		m_textureAssetsMap.clear();
	}

	TextureHandles TextureAssets::getTextureHandles(int id) const
	{
		return m_textureAssetsMap.at(id);
	}

	Vector2 TextureAssets::getTextureSize(int id, int splitTextureIndex) const
	{
		int textureSizeX = 0;
		int textureSizeY = 0;

		TextureHandles textureAssets = m_textureAssetsMap.at(id);
		int textureHandle = (splitTextureIndex == -1) ? textureAssets.textureHandle : textureAssets.splitTextureHandles.at(splitTextureIndex);

		DxLib::GetGraphSize(
			textureHandle,
			&textureSizeX,
			&textureSizeY
		);

		return Vector2(
			static_cast<float>(textureSizeX),
			static_cast<float>(textureSizeY)
		);
	}
}
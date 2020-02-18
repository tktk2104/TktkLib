#include "TktkDxlib2DWrapper/Assets/PixelShaderAssets/PixelShaderAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void PixelShaderAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_pixelShaderAssetsMap),
			std::end(m_pixelShaderAssetsMap),
			[](const auto& node) { DxLib::DeleteShader(node.second); }
		);
	}

	void PixelShaderAssets::loadPixelShader(int id, const std::string & assetFilePath)
	{
		erasePixelShader(id);

		int pixelShaderHandle = DxLib::LoadPixelShader(assetFilePath.c_str());

		m_pixelShaderAssetsMap.insert(std::make_pair(id, pixelShaderHandle));
	}

	void PixelShaderAssets::erasePixelShader(int id)
	{
		auto eraseNode = m_pixelShaderAssetsMap.find(id);
		if (eraseNode == std::end(m_pixelShaderAssetsMap)) return;

		DxLib::DeleteShader((*eraseNode).second);
		m_pixelShaderAssetsMap.erase(id);
	}

	void PixelShaderAssets::erasePixelShaderAll()
	{
		std::for_each(
			std::begin(m_pixelShaderAssetsMap),
			std::end(m_pixelShaderAssetsMap),
			[](const auto& node) { DxLib::DeleteShader(node.second); }
		);
		m_pixelShaderAssetsMap.clear();
	}

	int PixelShaderAssets::getPixelShaderHandle(int id) const
	{
		return m_pixelShaderAssetsMap.at(id);
	}
}
#include "TktkDxlib2DWrapper/Assets/MovieAssets/MovieAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void MovieAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_movieAssetsMap),
			std::end(m_movieAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second); }
		);
	}

	void MovieAssets::loadMovie(int id, const std::string & assetFilePath)
	{
		eraseMovie(id);

		int movieHandle = DxLib::LoadGraph(assetFilePath.c_str());

		m_movieAssetsMap.insert(std::make_pair(id, movieHandle));
	}

	void MovieAssets::eraseMovie(int id)
	{
		auto eraseNode = m_movieAssetsMap.find(id);
		if (eraseNode == std::end(m_movieAssetsMap)) return;

		DxLib::DeleteGraph((*eraseNode).second);
		m_movieAssetsMap.erase(id);
	}

	void MovieAssets::eraseMovieAll()
	{
		std::for_each(
			std::begin(m_movieAssetsMap),
			std::end(m_movieAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second); }
		);
		m_movieAssetsMap.clear();
	}

	int MovieAssets::getMovieHandle(int id) const
	{
		return m_movieAssetsMap.at(id);
	}

	Vector2 MovieAssets::getMovieSize(int id) const
	{
		int textureSizeX = 0;
		int textureSizeY = 0;

		DxLib::GetGraphSize(
			m_movieAssetsMap.at(id),
			&textureSizeX,
			&textureSizeY
		);

		return Vector2(
			static_cast<float>(textureSizeX),
			static_cast<float>(textureSizeY)
		);
	}
}
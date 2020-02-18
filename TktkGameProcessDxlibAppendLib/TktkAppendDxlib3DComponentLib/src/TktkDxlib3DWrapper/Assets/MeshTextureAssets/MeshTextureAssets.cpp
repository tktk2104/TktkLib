#include "TktkDxlib3DWrapper/Assets/MeshTextureAssets/MeshTextureAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void MeshTextureAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_meshTextureAssetsMap),
			std::end(m_meshTextureAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second); }
		);
	}

	void MeshTextureAssets::loadMeshTexture(int id, const std::string & assetFilePath)
	{
		eraseMeshTexture(id);

		int loadMeshTextureHandle = DxLib::MV1LoadTexture(assetFilePath.c_str());

		m_meshTextureAssetsMap.insert(std::make_pair(id, loadMeshTextureHandle));
	}

	void MeshTextureAssets::eraseMeshTexture(int id)
	{
		auto eraseNode = m_meshTextureAssetsMap.find(id);
		if (eraseNode == std::end(m_meshTextureAssetsMap)) return;

		DxLib::DeleteGraph((*eraseNode).second);
		m_meshTextureAssetsMap.erase(id);
	}

	void MeshTextureAssets::eraseMeshTextureAll()
	{
		std::for_each(
			std::begin(m_meshTextureAssetsMap),
			std::end(m_meshTextureAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second);; }
		);
		m_meshTextureAssetsMap.clear();
	}

	int MeshTextureAssets::getMeshTextureHandles(int id) const
	{
		return m_meshTextureAssetsMap.at(id);
	}
}
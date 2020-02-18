#include "TktkDxlib3DWrapper/Assets/VertexShaderAssets/VertexShaderAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void VertexShaderAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_vertexShaderAssetsMap),
			std::end(m_vertexShaderAssetsMap),
			[](const auto& node) { DxLib::DeleteShader(node.second); }
		);
	}

	void VertexShaderAssets::loadVertexShader(int id, const std::string & assetFilePath)
	{
		eraseVertexShader(id);

		int vertexShaderHandle = DxLib::LoadVertexShader(assetFilePath.c_str());

		m_vertexShaderAssetsMap.insert(std::make_pair(id, vertexShaderHandle));
	}

	void VertexShaderAssets::eraseVertexShader(int id)
	{
		auto eraseNode = m_vertexShaderAssetsMap.find(id);
		if (eraseNode == std::end(m_vertexShaderAssetsMap)) return;

		DxLib::DeleteShader((*eraseNode).second);
		m_vertexShaderAssetsMap.erase(id);
	}

	void VertexShaderAssets::eraseVertexShaderAll()
	{
		std::for_each(
			std::begin(m_vertexShaderAssetsMap),
			std::end(m_vertexShaderAssetsMap),
			[](const auto& node) { DxLib::DeleteShader(node.second); }
		);
		m_vertexShaderAssetsMap.clear();
	}

	int VertexShaderAssets::getVertexShaderHandle(int id) const
	{
		return m_vertexShaderAssetsMap.at(id);
	}
}
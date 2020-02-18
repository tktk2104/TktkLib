#include "TktkDxlib3DWrapper/Assets/MeshAssets/MeshAssets.h"

#include <stdexcept> // std::runtime_error
#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void MeshAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_meshAssetsMap),
			std::end(m_meshAssetsMap),
			[](const auto& node) { node.second.unLoadMesh(); }
		);
	}

	void MeshAssets::loadMesh(int id, const std::string & fileName)
	{
		eraseMesh(id);

		MeshHandles loadMeshHandle;
		loadMeshHandle.meshHandle = DxLib::MV1LoadModel(fileName.c_str());

		m_meshAssetsMap.insert(std::make_pair(id, loadMeshHandle));
	}

	void MeshAssets::loadMesh(int id, const std::string & modelFileName, std::vector<std::string> animFileNames)
	{
		eraseMesh(id);

		MeshHandles loadMeshHandle;
		loadMeshHandle.meshHandle = DxLib::MV1LoadModel(modelFileName.c_str());
		loadMeshHandle.animHandles.resize(animFileNames.size());

		auto animHandlesItr = std::begin(loadMeshHandle.animHandles);

		std::for_each(
			std::begin(animFileNames),
			std::end(animFileNames),
			[&animHandlesItr](const auto& node) { (*animHandlesItr++) = DxLib::MV1LoadModel(node.c_str()); }
		);

		m_meshAssetsMap.insert(std::make_pair(id, loadMeshHandle));
	}

	void MeshAssets::eraseMesh(int id)
	{
		auto eraseNode = m_meshAssetsMap.find(id);
		if (eraseNode == std::end(m_meshAssetsMap)) return;

		(*eraseNode).second.unLoadMesh();
		m_meshAssetsMap.erase(id);
	}

	void MeshAssets::eraseMeshAll()
	{
		std::for_each(
			std::begin(m_meshAssetsMap),
			std::end(m_meshAssetsMap),
			[](const auto& node) { node.second.unLoadMesh(); }
		);
		m_meshAssetsMap.clear();
	}

	MeshHandles MeshAssets::getMeshHandle(int id) const
	{
		if (m_meshAssetsMap.count(id) == 0)
		{
			throw std::runtime_error("modelAssets not found match id");
		}
		return m_meshAssetsMap.at(id);
	}
}
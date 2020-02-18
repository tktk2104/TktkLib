#ifndef MESH_ASSETS_H_
#define MESH_ASSETS_H_

#include <string>
#include <unordered_map>
#include "MeshHandles.h"

namespace tktk
{
	class MeshAssets
	{
	public:

		MeshAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadMesh(
			int id,
			const std::string& fileName
		);

		void loadMesh(
			int id,
			const std::string& modelFileName,
			std::vector<std::string> animFileNames
		);

		void eraseMesh(int id);

		void eraseMeshAll();

		MeshHandles getMeshHandle(int id) const;

	private:

		std::unordered_map<int, MeshHandles> m_meshAssetsMap;
	};
}
#endif // !MESH_ASSETS_H_
#ifndef MESH_TEXTURE_ASSETS_H_
#define MESH_TEXTURE_ASSETS_H_

#include <string>
#include <unordered_map>

namespace tktk
{
	class MeshTextureAssets
	{
	public:

		MeshTextureAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadMeshTexture(int id, const std::string & assetFilePath);

		void eraseMeshTexture(int id);

		void eraseMeshTextureAll();

		int getMeshTextureHandles(int id) const;

	private:

		std::unordered_map<int, int> m_meshTextureAssetsMap;
	};
}
#endif // !MESH_TEXTURE_ASSETS_H_

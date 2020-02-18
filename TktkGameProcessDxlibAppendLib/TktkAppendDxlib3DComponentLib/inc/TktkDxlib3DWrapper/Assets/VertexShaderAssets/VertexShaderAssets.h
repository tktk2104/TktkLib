#ifndef VERTEX_SHADER_ASSETS_H_
#define VERTEX_SHADER_ASSETS_H_

#include <string>
#include <unordered_map>

namespace tktk
{
	class VertexShaderAssets
	{
	public:

		VertexShaderAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadVertexShader(int id, const std::string & assetFilePath);

		void eraseVertexShader(int id);

		void eraseVertexShaderAll();

		int getVertexShaderHandle(int id) const;

	private:

		std::unordered_map<int, int> m_vertexShaderAssetsMap;
	};
}
#endif // !VERTEX_SHADER_ASSETS_H_
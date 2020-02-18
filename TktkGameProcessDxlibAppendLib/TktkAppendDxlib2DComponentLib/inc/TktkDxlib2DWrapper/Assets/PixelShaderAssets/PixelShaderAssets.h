#ifndef PIXEL_SHADER_ASSETS_H_
#define PIXEL_SHADER_ASSETS_H_

#include <string>
#include <unordered_map>

namespace tktk
{
	class PixelShaderAssets
	{
	public:

		PixelShaderAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadPixelShader(int id, const std::string & assetFilePath);

		void erasePixelShader(int id);

		void erasePixelShaderAll();

		int getPixelShaderHandle(int id) const;

	private:

		std::unordered_map<int, int> m_pixelShaderAssetsMap;
	};
}
#endif // !PIXEL_SHADER_ASSETS_H_
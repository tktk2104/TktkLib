#ifndef TEXTURE_ASSETS_H_
#define TEXTURE_ASSETS_H_

#include <string>
#include <unordered_map>
#include <TktkMath/Vector2.h>
#include "TextureHandles.h"

namespace tktk
{
	class TextureAssets
	{
	public:

		TextureAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadTexture(int id, const std::string & assetFilePath);

		void loadTexture(int id, const std::string & assetFilePath, int row, int column);

		void eraseTexture(int id);

		void eraseTextureAll();

		TextureHandles getTextureHandles(int id) const;

		Vector2 getTextureSize(int id, int splitTextureIndex = -1) const;

	private:

		std::unordered_map<int, TextureHandles> m_textureAssetsMap;
	};
}
#endif // !TEXTURE_ASSETS_H_

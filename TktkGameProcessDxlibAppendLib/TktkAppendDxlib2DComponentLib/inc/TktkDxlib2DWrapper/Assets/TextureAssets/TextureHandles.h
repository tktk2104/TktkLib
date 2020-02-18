#ifndef TEXTURE_HANDLES_H_
#define TEXTURE_HANDLES_H_

#include <vector>

namespace tktk
{
	// 未加工画像と分割画像のハンドルを格納する構造体
	struct TextureHandles
	{
	public:

		// 未加工画像と分割画像のハンドルをアンロードする
		void unLoadTexture() const;

	public:

		// 未加工画像のハンドル
		int textureHandle{ -1 };

		// 分割した画像のハンドルのリスト
		std::vector<int> splitTextureHandles;
	};
}
#endif // !TEXTURE_HANDLES_H_
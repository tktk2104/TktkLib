#include "TktkDxlib2DWrapper/Assets/TextureAssets/TextureHandles.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void TextureHandles::unLoadTexture() const
	{
		DxLib::DeleteGraph(textureHandle);

		std::for_each(
			std::begin(splitTextureHandles),
			std::end(splitTextureHandles),
			[](const auto& node) { DxLib::DeleteGraph(node); }
		);
	}
}
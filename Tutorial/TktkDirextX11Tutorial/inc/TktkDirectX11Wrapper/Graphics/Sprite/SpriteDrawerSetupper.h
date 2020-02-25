#ifndef SPRITE_DRAWER_SETUPPER_H_
#define SPRITE_DRAWER_SETUPPER_H_

#include <string>

namespace tktk
{
	// スプライトを描画する上での初期設定を行う
	class SpriteDrawerSetupper
	{
	public:

		static void setUp(
			const std::string& usePixelShaderFileName,
			const std::string& useVertexShaderFileName
		);
	};
}
#endif // !SPRITE_DRAWER_SETUPPER_H_
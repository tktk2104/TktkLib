#ifndef SPRITE_DRAWER_SETUPPER_H_
#define SPRITE_DRAWER_SETUPPER_H_

#include <string>

namespace tktk
{
	// �X�v���C�g��`�悷���ł̏����ݒ���s��
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
#ifndef LINE_2D_DRAWER_SETUPPER_H_
#define LINE_2D_DRAWER_SETUPPER_H_

#include <string>

namespace tktk
{
	// �Q�����̐�����`�悷�邽�߂̑O�������s���N���X
	class Line2DDrawerSetupper
	{
	public:

		static void setUp(
			const std::string& line2DPixelShaderFileName,
			const std::string& line2DVertexShaderFileName
		);
	};
}
#endif // !LINE_2D_DRAWER_SETUPPER_H_
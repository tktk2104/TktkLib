#ifndef LINE_2D_DRAWER_SETUPPER_H_
#define LINE_2D_DRAWER_SETUPPER_H_

#include <string>

namespace tktk
{
	// ２次元の線分を描画するための前準備を行うクラス
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
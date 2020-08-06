#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DDrawFuncArgs.h"

namespace tktk
{
	// ライン２Dの情報を管理するクラス
	// ※現状管理する情報は無い
	class Line2DData
	{
	public:

		Line2DData() = default;
		~Line2DData() = default;

	public:

		void drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const;

	private:

		// ライン描画用の頂点バッファを作る
		// ※前に作られた頂点バッファは削除される
		void createVertexBuffer(const std::vector<tktkMath::Vector2>& lineVertexArray) const;

		void updateLine2DCbuffer(const Line2DDrawFuncArgs& drawFuncArgs) const;
	};
}

#endif // !LINE_2D_DATA_H_
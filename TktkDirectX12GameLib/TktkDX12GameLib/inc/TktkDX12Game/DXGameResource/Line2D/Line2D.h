#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <memory>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DData.h"

namespace tktk
{
	// 「Line2DData」を管理するクラス
	// 現状は単一の「Line2DData」のみの管理
	class Line2D
	{
	public:

		Line2D(const ShaderFilePaths& shaderFilePaths);
		~Line2D() = default;

	public:

		// 線を描画する
		void drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const;

	private:

		// ２Ｄライン描画用のディスクリプタヒープを作る
		void craeteDescriptorHeap() const;

		// ２Ｄライン描画用のルートシグネチャを作る
		void createRootSignature() const;

		// ２Ｄライン描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		std::unique_ptr<Line2DData> m_line2DData;
	};
}
#endif // !LINE_2D_H_
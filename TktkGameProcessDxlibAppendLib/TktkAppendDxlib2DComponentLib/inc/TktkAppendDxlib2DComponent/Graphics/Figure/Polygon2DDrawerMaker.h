#ifndef POLYGON_2D_DRAWER_MAKER_H_
#define POLYGON_2D_DRAWER_MAKER_H_

#include <memory>
#include "Polygon2DDrawer.h"

namespace tktk
{
	struct Polygon2DDrawerMaker
	{
	public:

		// インスタンス作成開始
		static Polygon2DDrawerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<Polygon2DDrawer> create();

		// ポリゴンを形成する頂点の配列を設定（時計回り）
		Polygon2DDrawerMaker& vertexs(const std::vector<Vector2>& value);

		// ポリゴンを形成する頂点の配列を再設定（時計回り）
		template<class... Args>
		void vertexs(Args... value);

		// ポリゴンの線の太さを設定する
		Polygon2DDrawerMaker& lineThickness(float value);

		// 塗りつぶしフラグを設定する
		Polygon2DDrawerMaker& isFill(bool value);

		// ポリゴンの描画色を設定する
		Polygon2DDrawerMaker& polygonColor(const Color& value);

		// 描画優先度を設定する
		Polygon2DDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		Polygon2DDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		Polygon2DDrawerMaker& blendParam(float value);

		// 描画するレンダーターゲットを設定する
		Polygon2DDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static Polygon2DDrawerMaker m_self;

	private:

		std::vector<Vector2> m_vertexs;
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_polygonColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};

	template<class ...Args>
	inline void Polygon2DDrawerMaker::vertexs(Args ...value)
	{
		vertexs(std::vector<Vector2>({ value... }));
	}
}
#endif // !POLYGON_2D_DRAWER_MAKER_H_
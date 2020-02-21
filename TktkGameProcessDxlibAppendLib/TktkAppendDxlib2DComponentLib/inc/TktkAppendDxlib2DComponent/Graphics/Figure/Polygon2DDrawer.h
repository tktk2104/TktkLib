#ifndef POLYGON_2D_DRAWER_H_
#define POLYGON_2D_DRAWER_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// ２次元ポリゴンを描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class Polygon2DDrawer
		: public ComponentBase
	{
	public:

		Polygon2DDrawer(
			const std::vector<Vector2>& vertexs,
			float lineThickness,
			bool isFill,
			const Color& polygonColor,
			float drawPriority,
			BlendMode blendMode,
			float blendParam
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	private:

		void drawPolygon2D() const;

		void drawPolygon2DFlame() const;

	public:

		// ポリゴンを形成する頂点の配列を取得（時計回り）
		const std::vector<Vector2>& getVertexs() const;
		// ポリゴンを形成する頂点の配列を再設定（時計回り）
		void setVertexs(const std::vector<Vector2>& vertexs);

		// ポリゴンを形成する頂点の配列を再設定（時計回り）
		template<class... Args>
		void setVertexs(Args... vertexs);

		// 真円の線の太さを取得
		float getLineThickness() const;
		// 真円の線の太さを再設定
		void setLineThickness(float lineThickness);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;
		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// ポリゴンの描画色を取得
		const Color& getPolygonColor() const;
		// ポリゴンの描画色を再設定
		void setPolygonColor(const Color& polygonColor);

		// 描画のブレンド方法の種類を取得
		BlendMode getBlendMode() const;
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);

		// 描画のブレンドに使用する値を取得
		float getBlendParam() const;
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);

		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;

		// ポリゴンを形成する頂点の配列（時計回り）
		std::vector<Vector2> m_vertexs;

		// ポリゴンの線の太さ
		float m_lineThickness;

		// 塗りつぶしフラグ
		bool m_isFill;

		// ポリゴンの描画色
		Color m_polygonColor;

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;

		// レンダーターゲットに描画するか
		bool m_useRenderTarget{ false };

		// 描画するレンダーターゲットのId
		int m_renderTargetId{ -1 };
	};

	template<class ...Args>
	inline void Polygon2DDrawer::setVertexs(Args ...vertexs)
	{
		setVertexs(std::vector<Vector2>({ vertexs... }));
	}
}
#endif // !POLYGON_2D_DRAWER_H_
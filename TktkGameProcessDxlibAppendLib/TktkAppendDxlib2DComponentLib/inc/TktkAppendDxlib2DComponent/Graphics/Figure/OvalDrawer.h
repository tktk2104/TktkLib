#ifndef OVAL_DRAWER_H_
#define OVAL_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// 楕円を描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class OvalDrawer
		: public ComponentBase
	{
	public:

		OvalDrawer(
			const Vector2& ovalSize,		// 楕円の大きさ
			const Vector2& localPosition,	// 楕円のローカル座標
			float lineThickness,			// 楕円の線の太さ
			bool isFill,					// 塗りつぶしフラグ
			const Color& ovalColor,			// 楕円の描画色
			float drawPriority,				// 描画優先度
			BlendMode blendMode,			// 描画のブレンド方法の種類
			float blendParam,				// 描画のブレンドに使用する値
			bool useAntialiasing,			// アンチエイリアスの使用フラグ
			int vertexNum					// アンチエイリアスを使用する時に使う円を形作る頂点の数
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 楕円の大きさを取得
		const Vector2& getOvalSize() const;
		// 楕円の大きさを再設定
		void setOvalSize(const Vector2& ovalSize);

		// 楕円のローカル座標を取得
		const Vector2& getLocalPosition() const;
		// 楕円のローカル座標を再設定
		void setLocalPosition(const Vector2& localPosition);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;
		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// 楕円の描画色を取得
		const Color& getOvalColor() const;
		// 楕円の描画色を再設定
		void setOvalColor(const Color& ovalColor);

		// 描画のブレンド方法の種類を取得
		BlendMode getBlendMode() const;
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);

		// 描画のブレンドに使用する値を取得
		float getBlendParam() const;
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);

		// アンチエイリアスの使用フラグを取得
		bool getUseAntialiasing() const;
		// アンチエイリアスの使用フラグを再設定
		void setUseAntialiasing(bool useAntialiasing);

		// アンチエイリアスを使用する時に使う円を形作る頂点の数を取得
		int getVertexNum() const;
		// アンチエイリアスを使用する時に使う円を形作る頂点の数を再設定
		void setVertexNum(int vertexNum);

		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;

		// 楕円の大きさ
		Vector2 m_ovalSize;

		// 楕円のローカル座標
		Vector2 m_localPosition;

		// 真円の線の太さ
		float m_lineThickness;

		// 塗りつぶしフラグ
		bool m_isFill;

		// 楕円の描画色
		Color m_ovalColor;

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;

		// アンチエイリアスの使用フラグ
		bool m_useAntialiasing;

		// アンチエイリアスを使用する時に使う円を形作る頂点の数
		int m_vertexNum;

		// レンダーターゲットに描画するか
		bool m_useRenderTarget{ false };

		// 描画するレンダーターゲットのId
		int m_renderTargetId{ -1 };
	};
}
#endif // !OVAL_DRAWER_H_
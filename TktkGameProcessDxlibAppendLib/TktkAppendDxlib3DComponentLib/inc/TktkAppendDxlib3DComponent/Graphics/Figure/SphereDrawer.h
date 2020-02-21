#ifndef SPHERE_DRAWER_H_
#define SPHERE_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	// 球体を描画するコンポーネント
	// 【前提コンポーネント：Transform3D】
	class SphereDrawer
		: public ComponentBase
	{
	public:

		SphereDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// DxLibを使った3D描画で使用するパラメータ
			float radius,
			int divNum,
			bool isFill,
			const Color& sphereColor
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 球体の大きさを取得
		float getRadius() const;
		// 球体の大きさを再設定
		void setRadius(float radius);

		// 球体を描画する時のポリゴンの細かさを取得
		int getDivNum() const;
		// 球体を描画する時のポリゴンの細かさを再設定
		void setDivNum(int divNum);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;
		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// 球体の描画色を取得
		const Color& getSphereColor() const;
		// 球体の描画色を再設定
		void setSphereColor(const Color& sphereColor);

		// DxLibを使った3D描画で使用するパラメータを取得
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// 表示するメッシュのローカル行列を再設定
		void setMeshLocalMat(const Matrix4& localMat);
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);
		// ライトを使用して描画を行うかを再設定
		void setUseLight(bool useLight);
		// Zバッファを使用して描画を行うかを再設定
		void setWriteZBuffer(bool writeZBuffer);
		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の３次元座標コンポーネント
		CfpPtr<Transform3D> m_transform3D;

		// DxLibを使った3D描画で使用するパラメータ
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// 球体の半径
		float m_radius;

		// 球体を描画する時のポリゴンの細かさ
		int m_divNum;

		// 塗りつぶしフラグ
		bool m_isFill;

		// 球体の描画色
		Color m_sphereColor;
	};
}
#endif // !SPHERE_DRAWER_H_
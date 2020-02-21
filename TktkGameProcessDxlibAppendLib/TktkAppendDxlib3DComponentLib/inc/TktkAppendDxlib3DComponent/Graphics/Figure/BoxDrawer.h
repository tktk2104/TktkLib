#ifndef BOX_DRAWER_H_
#define BOX_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	// 立方体を描画するコンポーネント
	// 【前提コンポーネント：Transform3D】
	class BoxDrawer
		: public ComponentBase
	{
	public:

		BoxDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,
			const Vector3& boxSize,
			bool isFill,
			const Color& boxColor
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 立方体の大きさを取得
		const Vector3& getBoxSize() const;
		// 立方体の大きさを再設定
		void setBoxSize(const Vector3& boxSize);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;
		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// 立方体の描画色を取得
		const Color& getBoxColor() const;
		// 立方体の描画色を再設定
		void setBoxColor(const Color& boxColor);

		// DxLibを使った3D描画で使用するパラメータを取得
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// 表示する立方体のローカル行列を再設定
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

		// 立方体の大きさ
		Vector3 m_boxSize;

		// 塗りつぶしフラグ
		bool m_isFill;

		// 立方体の描画色
		Color m_boxColor;
	};
}
#endif // !BOX_DRAWER_H_

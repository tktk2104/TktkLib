#ifndef QUADRILATERALBILL_BOARD_DRAWER_H_
#define QUADRILATERALBILL_BOARD_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	// 四角形のビルボードを表示
	// ４点の座標を指定し作成した四角形をTransform3Dを使って移動・スケーリングさせ描画する
	// 【前提コンポーネント：Transform3D】
	// ※回転はできない
	// ※スケールはTransform3DのLocalScale.xyを使用
	class QuadrilateralBillboardDrawer
		: public ComponentBase
	{
	public:

		QuadrilateralBillboardDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// 
			int textureID,								// 描画するテクスチャID
			int splitTextureIndex,						// 描画するテクスチャの分割読み込み番号
			const Vector2& leftTopPos,					// 左上座標
			const Vector2& rightTopPos,					// 右上座標
			const Vector2& leftBottomPos,				// 左下座標
			const Vector2& rightBottomPos				// 右下座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 描画するテクスチャIDを取得する
		int getTextureID() const;
		// 描画するテクスチャIDを設定する
		void setTextureID(int textureID);

		// 描画するテクスチャの分割番号を取得
		int getSplitTextureIndex() const;
		// 描画するテクスチャの分割番号を設定
		void setSplitTextureIndex(int splitTextureIndex);

		// 左上座標を取得
		Vector2 getLeftTopPos() const;
		// 右上座標を取得
		Vector2 getRightTopPos() const;
		// 左下座標を取得
		Vector2 getLeftBottomPos() const;
		// 右下座標を取得
		Vector2 getRightBottomPos() const;

		// 左上座標を設定
		void setLeftTopPos(const Vector2& leftTopPos);
		// 右上座標を設定
		void setRightTopPos(const Vector2& rightTopPos);
		// 左下座標を設定
		void setLeftBottomPos(const Vector2& leftBottomPos);
		// 右下座標を設定
		void setRightBottomPos(const Vector2& rightBottomPos);

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

		// 描画するテクスチャID
		int m_textureID{ -1 };

		// 描画するテクスチャの分割読み込み番号
		int m_splitTextureIndex{ -1 };

		// 左上座標
		Vector2 m_leftTopPos;

		// 右上座標
		Vector2 m_rightTopPos;

		// 左下座標
		Vector2 m_leftBottomPos;

		// 右下座標
		Vector2 m_rightBottomPos;
	};
}
#endif // !QUADRILATERALBILL_BOARD_DRAWER_H_
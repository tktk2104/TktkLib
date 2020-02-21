#ifndef RECT_BILLBOARD_DRAWER_H_
#define RECT_BILLBOARD_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	class RectBillboardDrawer
		: public tktk::ComponentBase
	{
	public:

		RectBillboardDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,
			int textureId,								// 表示するテクスチャのId
			int splitTextureIndex,						// 表示するテクスチャの分割読み込み番号
			const Vector2& rotateCenterRate,			// 回転させるときの中心位置（割合）
			float billboardScaleRate					// ビルボードのスケール（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 描画するテクスチャIDを取得する
		int getTextureID() const;
		// 描画するテクスチャIDを再設定する
		void setTextureID(int textureID);

		// 描画するテクスチャの分割読み込み番号を取得する
		int getSplitTextureIndex() const;
		// 描画するテクスチャの分割読み込み番号を再設定する
		void setSplitTextureIndex(int splitTextureIndex);

		// ビルボードのスケールを取得（割合）
		float getBillboardScaleRate() const;
		// ビルボードのスケールを再設定（割合）
		void setBillboardScaleRate(float billboardScaleRate);

		// 回転させるときの中心位置を取得（割合）
		const Vector2& getRotateCenterRate() const;
		// 回転させるときの中心位置を再設定（割合）
		void setRotateCenterRate(const Vector2& rotateCenterRate);

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

		// 回転させるときの中心位置（割合）
		Vector2 m_rotateCenterRate{ Vector2(0.5f, 0.5f) };

		// ビルボードのスケール
		float m_billboardScaleRate{ 1.0f };
	};
}
#endif // !RECT_BILLBOARD_DRAWER_H_
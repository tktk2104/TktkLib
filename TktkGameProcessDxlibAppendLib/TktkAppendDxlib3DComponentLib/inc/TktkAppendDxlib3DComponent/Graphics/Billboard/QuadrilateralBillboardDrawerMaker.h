#ifndef QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_
#define QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_

#include "QuadrilateralBillboardDrawer.h"

namespace tktk
{
	class QuadrilateralBillboardDrawerMaker
	{
	public:

		// インスタンス作成開始
		static QuadrilateralBillboardDrawerMaker& makeStart();

	public:

		// 作成する
		QuadrilateralBillboardDrawer* create();

		// 描画優先度を設定する
		QuadrilateralBillboardDrawerMaker& drawPriority(float value);

		// 表示するテクスチャのIdを設定する
		QuadrilateralBillboardDrawerMaker& textureId(int value);

		// 表示するテクスチャの分割読み込み番号を設定する
		QuadrilateralBillboardDrawerMaker& splitTextureIndex(int value);

		// ビルボードのローカル座標を設定する
		QuadrilateralBillboardDrawerMaker& localPos(const Vector3& value);

		// 左上座標を設定する
		QuadrilateralBillboardDrawerMaker& leftTopPos(const Vector2& value);

		// 右上座標を設定する
		QuadrilateralBillboardDrawerMaker& rightTopPos(const Vector2& value);

		// 左下座標を設定する
		QuadrilateralBillboardDrawerMaker& leftBottomPos(const Vector2& value);

		// 右下座標を設定する
		QuadrilateralBillboardDrawerMaker& rightBottomPos(const Vector2& value);

		// 描画のブレンド方法の種類を設定する
		QuadrilateralBillboardDrawerMaker& blendMode(const BlendMode& value);

		// 描画のブレンドに使用する値を設定する
		QuadrilateralBillboardDrawerMaker& blendParam(float value);

		// ライトを使用して描画を行うか？
		QuadrilateralBillboardDrawerMaker& useLight(bool value);

		// Zバッファを使用して描画を行うか?
		QuadrilateralBillboardDrawerMaker& writeZBuffer(bool value);

		// 描画するレンダーターゲットを設定する
		QuadrilateralBillboardDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static QuadrilateralBillboardDrawerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		Vector3 m_localPos{ Vector3::zero };
		Vector2 m_leftTopPos	{ Vector2(-0.5f, -0.5f) };
		Vector2 m_rightTopPos	{ Vector2( 0.5f, -0.5f) };
		Vector2 m_leftBottomPos	{ Vector2(-0.5f,  0.5f) };
		Vector2 m_rightBottomPos{ Vector2( 0.5f,  0.5f) };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
	};
}
#endif // !QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_
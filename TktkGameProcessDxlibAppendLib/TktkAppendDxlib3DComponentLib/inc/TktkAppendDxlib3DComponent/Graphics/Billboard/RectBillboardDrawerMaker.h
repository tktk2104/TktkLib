#ifndef RECT_BILLBOARD_DRAWER_MAKER_H_
#define RECT_BILLBOARD_DRAWER_MAKER_H_

#include "RectBillboardDrawer.h"

namespace tktk
{
	class RectBillboardDrawerMaker
	{
	public:

		// インスタンス作成開始
		static RectBillboardDrawerMaker& makeStart();

	public:

		// 作成する
		RectBillboardDrawer* create();

		// 描画優先度を設定する
		RectBillboardDrawerMaker& drawPriority(float value);

		// 表示するテクスチャのIdを設定する
		RectBillboardDrawerMaker& textureId(int value);

		// 表示するテクスチャの分割読み込み番号を設定する
		RectBillboardDrawerMaker& splitTextureIndex(int value);

		// ビルボードのローカル座標を設定する
		RectBillboardDrawerMaker& localPos(const Vector3& value);

		// 回転させるときの中心位置（割合）を設定する
		RectBillboardDrawerMaker& rotateCenterRate(const Vector2& value);

		// ビルボードのスケール（割合）を設定する
		RectBillboardDrawerMaker& billboardScaleRate(float value);

		// 描画のブレンド方法の種類を設定する
		RectBillboardDrawerMaker& blendMode(const BlendMode& value);

		// 描画のブレンドに使用する値を設定する
		RectBillboardDrawerMaker& blendParam(float value);

		// ライトを使用して描画を行うか？
		RectBillboardDrawerMaker& useLight(bool value);

		// Zバッファを使用して描画を行うか?
		RectBillboardDrawerMaker& writeZBuffer(bool value);

		// 描画するレンダーターゲットを設定する
		RectBillboardDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static RectBillboardDrawerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		Vector3 m_localPos{ Vector3::zero };
		Vector2 m_rotateCenterRate{ Vector2(0.5f, 0.5f) };
		float m_billboardScaleRate{ 1.0f };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_BILLBOARD_DRAWER_MAKER_H_

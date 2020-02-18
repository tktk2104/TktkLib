#ifndef DXLIB_DRAW_3D_PARAM_H_
#define DXLIB_DRAW_3D_PARAM_H_

#include <TktkMath/Matrix4.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>

namespace tktk
{
	struct DxLibDraw3DParam
	{
		explicit DxLibDraw3DParam(float drawPriority);

		DxLibDraw3DParam(
			float drawPriority,
			const Matrix4& localMat,
			BlendMode blendMode,
			float blendParam,
			bool useLight,
			bool writeZBuffer,
			int renderTargetId,
			bool createShadow,
			float shadowCreatorPriority
		);

		// 描画優先度（定数）
		const float drawPriority;

		// 描画位置のローカル座標
		Matrix4 localMat{ Matrix4::identity };

		// 描画のブレンド方法の種類
		BlendMode blendMode{ BlendMode::None };

		// 描画のブレンドに使用する値
		float blendParam{ 1.0f };

		// ライトを使用して描画を行うか？
		bool useLight{ true };

		// Zバッファを使用して描画を行うか？
		bool writeZBuffer{ true };

		// 描画するレンダーターゲットのId（-1で画面に直接描画）
		int renderTargetId{ -1 };

		// 影を生成するか？
		bool createShadow{ false };

		// シャドウマップの生成を行う描画優先度
		float shadowCreatorPriority{ 100 };
	};
}
#endif // !DXLIB_DRAW_3D_PARAM_H_

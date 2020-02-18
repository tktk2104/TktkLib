#ifndef BLEND_MODE_H_
#define BLEND_MODE_H_

namespace tktk
{
	// 色のブレンド方法の種類
	enum BlendMode
	{
		None = 0,	// ブレンドしない
		Alpha = 1,	// アルファブレンド
		Add = 2,	// 加算ブレンド
		Sub = 3		// 減算ブレンド
	};
}
#endif // !BLEND_MODE_H_
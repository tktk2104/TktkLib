#ifndef REVERSE_FLAG_H_
#define REVERSE_FLAG_H_

namespace tktk
{
	// 反転ビットフラグ
	enum ReverseFlag
	{
		// 水平方向の反転（垂直な線を軸にして反転）
		HORIZONTAL_REVERSE	= 1 << 0,

		// 垂直方向の反転（水平な線を軸にして反転）
		VERTICAL_REVERSE	= 1 << 1,

		// 反転無し
		NOT_REVERSE = 0,
	};
}

#endif // !REVERSE_FLAG_H_
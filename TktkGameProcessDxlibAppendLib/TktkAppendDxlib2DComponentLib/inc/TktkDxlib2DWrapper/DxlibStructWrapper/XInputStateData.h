#ifndef XINPUT_STATE_DATA_H_
#define XINPUT_STATE_DATA_H_

namespace tktk
{
	struct XInputStateData
	{
		unsigned char	buttons[16];	// ボタン１６個( 添字には XINPUT_BUTTON_DPAD_UP 等を使用する、0:押されていない  1:押されている )
		unsigned char	leftTrigger;	// 左トリガー( 0～255 )
		unsigned char	rightTrigger;	// 右トリガー( 0～255 )
		short			thumbLX;		// 左スティックの横軸値( -32768 ～ 32767 )
		short			thumbLY;		// 左スティックの縦軸値( -32768 ～ 32767 )
		short			thumbRX;		// 右スティックの横軸値( -32768 ～ 32767 )
		short			thumbRY;		// 右スティックの縦軸値( -32768 ～ 32767 )
	};
}
#endif // !XINPUT_STATE_DATA_H_



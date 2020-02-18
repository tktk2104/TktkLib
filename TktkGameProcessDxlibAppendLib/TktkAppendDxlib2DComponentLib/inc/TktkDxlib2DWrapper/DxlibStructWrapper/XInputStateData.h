#ifndef XINPUT_STATE_DATA_H_
#define XINPUT_STATE_DATA_H_

namespace tktk
{
	struct XInputStateData
	{
		unsigned char	buttons[16];	// �{�^���P�U��( �Y���ɂ� XINPUT_BUTTON_DPAD_UP �����g�p����A0:������Ă��Ȃ�  1:������Ă��� )
		unsigned char	leftTrigger;	// ���g���K�[( 0�`255 )
		unsigned char	rightTrigger;	// �E�g���K�[( 0�`255 )
		short			thumbLX;		// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
		short			thumbLY;		// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
		short			thumbRX;		// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
		short			thumbRY;		// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
	};
}
#endif // !XINPUT_STATE_DATA_H_



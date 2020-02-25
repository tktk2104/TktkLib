#ifndef KEY_BOARD_H_
#define KEY_BOARD_H_

#include "KeybordKeyType.h"

namespace tktk
{
	// 「KeyboardManager」の実装の一部を隠すためのクラス
	class Keyboard
	{
	public:

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);
	};
}
#endif // !KEY_BOARD_H_
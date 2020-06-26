#ifndef KEY_BOARD_MANAGER_H_
#define KEY_BOARD_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "KeyboardUpdater.h"
#include "KeybordKeyType.h"
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// 「KeyboardUpdater」に簡単にアクセスするためのクラス
	class KeyboardManager
	{
	public:

		// 「KeyboardUpdater」を生成
		static void setUp(HINSTANCE hInstance);

	public:

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	private:

		static CfpPtr<KeyboardUpdater> m_updaterPtr;
	};
}
#endif // !KEY_BOARD_MANAGER_H_
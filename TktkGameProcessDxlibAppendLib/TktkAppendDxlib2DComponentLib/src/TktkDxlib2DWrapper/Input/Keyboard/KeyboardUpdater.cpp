#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardUpdater.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void KeyboardUpdater::update()
	{
		std::copy(
			std::begin(m_curKeycode),
			std::end(m_curKeycode),
			std::begin(m_preKeycode)
		);
		GetHitKeyStateAll(m_curKeycode);
	}

	bool KeyboardUpdater::getState(int inputType, KeyboardKeyType keyboardKeyType)
	{
		if ((inputType & INPUT_BEGIN) != 0)
		{
			if (m_curKeycode[keyboardKeyType] == 1
				&& m_preKeycode[keyboardKeyType] == 0) return true;
		}

		if ((inputType & INPUT_PUSHING) != 0)
		{
			if (m_curKeycode[keyboardKeyType] == 1) return true;
		}

		if ((inputType & INPUT_ENDED) != 0)
		{
			if (m_curKeycode[keyboardKeyType] == 0
				&& m_preKeycode[keyboardKeyType] == 1) return true;
		}
		return false;
	}
}
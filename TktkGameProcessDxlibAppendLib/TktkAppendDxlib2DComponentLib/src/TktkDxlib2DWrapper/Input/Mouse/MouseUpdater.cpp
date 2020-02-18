#include "TktkDxlib2DWrapper/Input/Mouse/MouseUpdater.h"

#include <DxLib.h>
#include "TktkDxlib2DWrapper/Input/InputType.h"

namespace tktk
{
	void MouseUpdater::update()
	{
		m_preState = m_curState;
		m_curState = DxLib::GetMouseInput();
	}

	Vector2 MouseUpdater::getCursorPoint()
	{
		int x = 0;
		int y = 0;
		DxLib::GetMousePoint(&x, &y);
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	void MouseUpdater::setCursorPoint(const Vector2 & point)
	{
		DxLib::SetMousePoint(static_cast<int>(point.x), static_cast<int>(point.y));
	}

	void MouseUpdater::showCursor()
	{
		DxLib::SetMouseDispFlag(TRUE);
	}

	void MouseUpdater::hideCursor()
	{
		DxLib::SetMouseDispFlag(FALSE);
	}

	bool MouseUpdater::getState(int inputType, int mouseButtonType)
	{
		if ((inputType & INPUT_BEGIN) != 0)
		{
			if ((m_curState & ~m_preState & mouseButtonType) != 0) return true;
		}

		if ((inputType & INPUT_PUSHING) != 0)
		{
			if ((m_curState & mouseButtonType) != 0) return true;
		}

		if ((inputType & INPUT_ENDED) != 0)
		{
			if ((~m_curState & m_preState & mouseButtonType) != 0) return true;
		}
		return false;
	}

	int MouseUpdater::getVerticalMouseWheel()
	{
		return DxLib::GetMouseWheelRotVol();
	}

	float MouseUpdater::getVerticalMouseWheelF()
	{
		return DxLib::GetMouseWheelRotVolF();
	}

	int MouseUpdater::getHorizontalMouseWheel()
	{
		return DxLib::GetMouseHWheelRotVol();
	}

	float MouseUpdater::getHorizontalMouseWheelF()
	{
		return DxLib::GetMouseHWheelRotVolF();
	}
}
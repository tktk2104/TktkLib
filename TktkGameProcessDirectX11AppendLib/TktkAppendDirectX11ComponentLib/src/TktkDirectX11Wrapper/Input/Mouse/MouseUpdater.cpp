#include "TktkDirectX11Wrapper/Input/Mouse/MouseUpdater.h"

#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	MouseUpdater::MouseUpdater()
		: m_curMouseButtonState{ { MouseButtonType::leftBtn, false }, { MouseButtonType::rightBtn, false }, { MouseButtonType::centerBtn, false } }
		, m_preMouseButtonState{ m_curMouseButtonState }
	{
	}

	void MouseUpdater::update()
	{
		std::swap(m_curMouseButtonState, m_preMouseButtonState);

		for (auto& pair : m_curMouseButtonState)
		{
			pair.second = GetAsyncKeyState(static_cast<int>(pair.first));
		}
	}

	Vector2 MouseUpdater::mousePos() const
	{
		POINT tempMousePos;
		GetCursorPos(&tempMousePos);
		return Vector2(static_cast<float>(tempMousePos.x), static_cast<float>(tempMousePos.y));
	}

	bool MouseUpdater::isPush(MouseButtonType buttonType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (buttonType == MouseButtonType::leftBtn) return m_curMouseButtonState.at(MouseButtonType::rightBtn);
			if (buttonType == MouseButtonType::rightBtn) return m_curMouseButtonState.at(MouseButtonType::leftBtn);
		}
		return m_curMouseButtonState.at(buttonType);
	}

	bool MouseUpdater::isTrigger(MouseButtonType buttonType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (buttonType == MouseButtonType::leftBtn) 
				return (m_curMouseButtonState.at(MouseButtonType::rightBtn) && !m_preMouseButtonState.at(MouseButtonType::rightBtn));

			if (buttonType == MouseButtonType::rightBtn) 
				return (m_curMouseButtonState.at(MouseButtonType::leftBtn) && !m_preMouseButtonState.at(MouseButtonType::leftBtn));
		}
		return (m_curMouseButtonState.at(buttonType) && !m_preMouseButtonState.at(buttonType));
	}
}
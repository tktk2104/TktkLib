#include "TktkDirectX11Wrapper/Input/Keyboard/KeyboardUpdater.h"

#include <algorithm>
#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace tktk
{
	KeyboardUpdater::KeyboardUpdater(
		HINSTANCE hInstance
	)
	{
		std::fill(std::begin(m_curKeys), std::end(m_curKeys), 0U);

		std::fill(std::begin(m_preKeys), std::end(m_preKeys), 0U);

		DirectInput8Create(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)(&m_input),
			NULL
		);

		m_input->CreateDevice(
			GUID_SysKeyboard,
			&m_inputDevice,
			NULL
		);

		m_inputDevice->SetDataFormat(
			&c_dfDIKeyboard
		);

		m_inputDevice->SetCooperativeLevel(
			Window::getHWND(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
		);

		m_inputDevice->Acquire();
	}

	KeyboardUpdater::~KeyboardUpdater()
	{
		if (m_input != nullptr)
		{
			m_input->Release();
		}

		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void KeyboardUpdater::update()
	{
		std::copy(
			std::begin(m_curKeys),
			std::end(m_curKeys),
			std::begin(m_preKeys)
		);

		HRESULT ret = m_inputDevice->GetDeviceState(sizeof(unsigned char) * m_curKeys.size(), m_curKeys.data());
	
		if (FAILED(ret))
		{
			m_inputDevice->Acquire();
			m_inputDevice->GetDeviceState(sizeof(unsigned char) * m_curKeys.size(), m_curKeys.data());
		}
	}

	bool KeyboardUpdater::isPush(KeybordKeyType keyType)
	{
		return (m_curKeys.at(keyType) & 0x80);
	}

	bool KeyboardUpdater::isTrigger(KeybordKeyType keyType)
	{
		return ((m_curKeys.at(keyType) & 0x80) && !(m_preKeys.at(keyType) & 0x80));
	}
}
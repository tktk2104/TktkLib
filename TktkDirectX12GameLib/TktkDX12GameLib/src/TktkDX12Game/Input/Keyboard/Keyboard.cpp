#include "TktkDX12Game/Input/Keyboard/Keyboard.h"

#include <algorithm>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace tktk
{
	Keyboard::Keyboard(HINSTANCE hInstance, HWND handle)
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

		m_input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, NULL);

		m_inputDevice->SetDataFormat(&c_dfDIKeyboard);

		m_inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		m_inputDevice->Acquire();
	}

	Keyboard::~Keyboard()
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

	void Keyboard::update()
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

	bool Keyboard::isPush(KeybordKeyType keyType)
	{
		return (m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80);
	}

	bool Keyboard::isTrigger(KeybordKeyType keyType)
	{
		return ((m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80) && !(m_preKeys.at(static_cast<unsigned int>(keyType)) & 0x80));
	}
}
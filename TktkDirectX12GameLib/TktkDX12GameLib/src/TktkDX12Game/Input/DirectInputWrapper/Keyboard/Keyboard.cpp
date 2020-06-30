#include "TktkDX12Game/Input/DirectInputWrapper/Keyboard/Keyboard.h"

#include <algorithm>

namespace tktk
{
	Keyboard::Keyboard(LPDIRECTINPUT8 input, HWND handle)
	{
		// ���ꂼ��̃L�[���͏�������������
		std::fill(std::begin(m_curKeys), std::end(m_curKeys), 0U);
		std::fill(std::begin(m_preKeys), std::end(m_preKeys), 0U);

		// �f�t�H���g�̃V�X�e���L�[�{�[�h���g�p����ݒ�Ńf�o�C�X���쐬
		input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, NULL);

		// �L�[�{�[�h�̓��̓f�o�C�X�ł��鎖��ݒ�
		m_inputDevice->SetDataFormat(&c_dfDIKeyboard);

		// �L�[�{�[�h�̔r��������Z�b�g����
		m_inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		// ����J�n
		m_inputDevice->Acquire();
	}

	Keyboard::~Keyboard()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void Keyboard::update()
	{
		// �O�t���[���̓��͏󋵂��X�V����
		std::copy(
			std::begin(m_curKeys),
			std::end(m_curKeys),
			std::begin(m_preKeys)
		);

		// ���͂̎擾�����݂�
		HRESULT ret = m_inputDevice->GetDeviceState(sizeof(unsigned char) * m_curKeys.size(), m_curKeys.data());
	
		// ���͓��삪��~���Ă����ꍇ
		if (FAILED(ret))
		{
			// ������ĊJ���čĎ擾�����݂�
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
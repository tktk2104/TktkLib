#include "TktkDX12Game/Input/DirectInputWrapper/GamePad/GamePad.h"

#include <algorithm>

namespace tktk
{
	struct CallBackFuncArgs
	{
		LPDIRECTINPUT8			input		{ nullptr };
		LPDIRECTINPUTDEVICE8*	inputDevice	{ nullptr };
		HWND					handle		{ nullptr };
	};

	BOOL CALLBACK EnumJoyDeviceProc(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
	{
		CallBackFuncArgs* args = reinterpret_cast<CallBackFuncArgs*>(pContext);

		// �W���C�X�e�B�b�N�f�o�C�X�̍쐬
		HRESULT ret = args->input->CreateDevice(pdidInstance->guidInstance, args->inputDevice, NULL);
		if (FAILED(ret))
		{
			// �f�o�C�X�쐬���s
			return DIENUM_STOP;
		}

		// ���̓f�[�^�`���̃Z�b�g
		ret = (*args->inputDevice)->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(ret))
		{
			// ���̓f�[�^�`���̃Z�b�g���s
			(*args->inputDevice)->Release();
			return DIENUM_STOP;
		}

		// �r������̃Z�b�g
		ret = (*args->inputDevice)->SetCooperativeLevel(args->handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
		if (FAILED(ret))
		{
			// �r������̃Z�b�g���s
			(*args->inputDevice)->Release();
			return DIENUM_STOP;
		}

		// ���͔͈͂̃Z�b�g
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMax = 1000;
		diprg.lMin = -1000;

		// X��
		diprg.diph.dwObj = DIJOFS_X;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// Y��
		diprg.diph.dwObj = DIJOFS_Y;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// Z��
		diprg.diph.dwObj = DIJOFS_Z;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RX��
		diprg.diph.dwObj = DIJOFS_RX;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RY��
		diprg.diph.dwObj = DIJOFS_RY;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RZ��
		diprg.diph.dwObj = DIJOFS_RZ;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �N����������
		(*args->inputDevice)->Poll();

		/* �\�z�����Ȃ�
		DEBUG("�C���X�^���X�̓o�^�� [%s]\n", lpddi->tszInstanceName);
		DEBUG("���i�̓o�^��         [%s]\n", lpddi->tszProductName);
		DEBUG("�\�z����\n");*/

		// �ŏ���1�݂̂ŏI���
		return DIENUM_STOP;         // ���̃f�o�C�X��񋓂���ɂ�DIENUM_CONTINUE��Ԃ�
	}

	GamePad::GamePad(LPDIRECTINPUT8 input, HWND handle)
	{
		// ���ꂼ��̃L�[���͏�������������
		m_curPadState = std::make_unique<DIJOYSTATE2>();
		m_prePadState = std::make_unique<DIJOYSTATE2>();
		ZeroMemory(m_curPadState.get(), sizeof(DIJOYSTATE2));
		ZeroMemory(m_prePadState.get(), sizeof(DIJOYSTATE2));

		// �R�[���o�b�N�֐��ɕK�v�Ȉ���
		CallBackFuncArgs callBackFuncArgs{ input, &m_inputDevice, handle };

		// �ڑ�����Ă���Q�[���p�b�h��T���A�ŏ��Ɍ��������Ńf�o�C�X���쐬����
		input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyDeviceProc, &callBackFuncArgs, DIEDFL_ATTACHEDONLY);

		// �Q�[���p�b�h���ڑ�����Ă�����
		if (m_inputDevice)
		{
			// �Q�[���p�b�h�ڑ���Ԃɂ���
			m_findGamePad = true;

			// ����J�n
			m_inputDevice->Acquire();
		}
	}

	GamePad::~GamePad()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void GamePad::update()
	{
		// �R���g���[���[���ڑ�����Ă��Ȃ������牽�����Ȃ�
		if (!m_findGamePad) return;

		// ���݂ƂP�t���[���O�̓��͏������ւ���
		m_curPadState.swap(m_prePadState);

		// Poll���s��
		m_inputDevice->Poll();

		// �ی��Ƃ��ă[���N���A����
		ZeroMemory(m_curPadState.get(), sizeof(DIJOYSTATE2));

		// ���͂̎擾�����݂�
		HRESULT ret = m_inputDevice->GetDeviceState(sizeof(DIJOYSTATE2), m_curPadState.get());

		// ���͓��삪��~���Ă����ꍇ
		if (FAILED(ret))
		{
			// ������ĊJ����
			m_inputDevice->Acquire();
		}
	}

	tktkMath::Vector2 GamePad::getLstick() const
	{
		return { static_cast<float>(m_curPadState->lX) / 1000.0f, static_cast<float>(m_curPadState->lY) / 1000.0f };
	}

	tktkMath::Vector2 GamePad::getRstick() const
	{
		return { static_cast<float>(m_curPadState->lZ) / 1000.0f, static_cast<float>(m_curPadState->lRz) / 1000.0f };
	}

	bool GamePad::isPush(GamePadBtnType keyType) const
	{
		return (m_curPadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80);
	}

	bool GamePad::isTrigger(GamePadBtnType keyType) const
	{
		return ((m_curPadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80) && !(m_prePadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80));
	}
}
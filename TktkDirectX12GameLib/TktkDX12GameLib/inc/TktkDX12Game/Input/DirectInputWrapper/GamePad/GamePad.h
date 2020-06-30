#ifndef GAME_PAD_H_
#define GAME_PAD_H_

#include <memory>
#include <array>
#include <TktkMath/Structs/Vector2.h>
#include "../DirectInputIncluder.h"
#include "GamePadBtnType.h"

namespace tktk
{
	class GamePad
	{
	public:

		GamePad(LPDIRECTINPUT8 input, HWND handle);
		~GamePad();

	public:

		void update();

	public:

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getLstick() const;

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getRstick() const;

		// �w��̃{�^����������Ă��邩�𔻒�
		bool isPush(GamePadBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		// �C���v�b�g�f�o�C�X
		LPDIRECTINPUTDEVICE8			m_inputDevice{ nullptr };

		// �Q�[���p�b�h�����������H
		bool							m_findGamePad{ false };

		// ���݂̃p�b�h���͏��
		std::unique_ptr<DIJOYSTATE2>	m_curPadState;

		// �O�t���[���̃p�b�h���͏��
		std::unique_ptr<DIJOYSTATE2>	m_prePadState;
	};
}
#endif // !GAME_PAD_H_
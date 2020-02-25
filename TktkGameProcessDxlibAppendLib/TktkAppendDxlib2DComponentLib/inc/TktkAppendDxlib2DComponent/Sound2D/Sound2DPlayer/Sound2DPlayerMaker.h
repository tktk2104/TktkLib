#ifndef SOUND_2D_PLAYER_MAKER_H_
#define SOUND_2D_PLAYER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Sound2DPlayer.h"

namespace tktk
{
	class Sound2DPlayerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static Sound2DPlayerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<Sound2DPlayer> create();

		// ���g�̐����シ���ɍĐ����邩��ݒ�
		Sound2DPlayerMaker& startToPlay(bool value);

		// �Đ�����T�E���h��ID��ݒ�
		Sound2DPlayerMaker& playSoundId(int value);

		// �Đ����@�̎�ނ�ݒ�
		Sound2DPlayerMaker& soundPlayType(SoundPlayType value);

		// �čĐ��̎��ŏ�����Đ����邩��ݒ�
		Sound2DPlayerMaker& playFromTop(bool value);

		// �T�E���h�Đ��Ŏg�p����p����ݒ�
		Sound2DPlayerMaker& panPalRate(float value);

		// �T�E���h�Đ��Ŏg�p����{�����[����ݒ�
		Sound2DPlayerMaker& volumeRate(float value);

	private:

		// ���g�̃|�C���^
		static Sound2DPlayerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		bool m_startToPlay{ true };
		int m_playSoundId{ -1 };
		SoundPlayType m_soundPlayType{ SoundPlayType::SOUND_PLAY_TYPE_BACKGROUND };
		bool m_playFromTop{ true };
		bool m_useDefaltPanPalRate{ true };
		bool m_useDefaltVolumeRate{ true };
		float m_panPalRate{ 0.5f };
		float m_volumeRate{ 1.0f };
	};
}
#endif // !SOUND_2D_PLAYER_MAKER_H_
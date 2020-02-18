#ifndef SOUND_2D_PLAYER_H_
#define SOUND_2D_PLAYER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib2DWrapper/Sound2D/SoundPlayType.h"

namespace tktk
{
	// �T�E���h�Đ��R���|�[�l���g
	class Sound2DPlayer
		: public ComponentBase
	{
	public:

		Sound2DPlayer(
			bool startToPlay,				// ���g�̐����シ���ɍĐ����邩�H
			int playSoundId,				// �Đ�����T�E���h��ID
			SoundPlayType soundPlayType,	// �Đ����@�̎��
			bool playFromTop,				// �čĐ��̎��ŏ�����Đ����邩�H
			bool useDefaltPanPalRate,		// �f�t�H���g�̃p�����g�p���邩�H�i�����j
			bool useDefaltVolumeRate,		// �f�t�H���g�̃{�����[�����g�p���邩�H�i�����j
			float panPalRate,				// �T�E���h�Đ��Ŏg�p����p��
			float volumeRate				// �T�E���h�Đ��Ŏg�p����{�����[��
		);

	public:

		void start();

	public:

		// �T�E���h���Đ�����
		void playSound();
		// �T�E���h���~����
		void stopSound();

		// �T�E���h���Đ������H
		bool isPlaySound();

		// �Đ�����T�E���h��ID���Đݒ�
		void setPlaySoundId(int playSoundId);

		// �Đ����@�̎�ނ��Đݒ�
		void setSoundPlayType(SoundPlayType soundPlayType);

		// �čĐ��̎��ŏ�����Đ����邩���Đݒ�
		void setPlayFromTop(bool playFromTop);

		// �T�E���h�Đ��Ŏg�p����p�����Đݒ�
		void setPanPalRate(float panPalRate);
		// �f�t�H���g�̃p�����g�p����
		void useDefaltPanPalRate();

		// �T�E���h�Đ��Ŏg�p����{�����[�����Đݒ�
		void setVolumeRate(float volumeRate);
		// �f�t�H���g�̃{�����[�����g�p����
		void useDefaltVolumeRate();

	private:

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
#endif // !SOUND_2D_PLAYER_H_
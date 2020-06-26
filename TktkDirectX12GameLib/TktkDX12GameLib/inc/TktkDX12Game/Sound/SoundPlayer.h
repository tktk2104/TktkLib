#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <string>
#include <xaudio2.h>
#include "Sound.h"

namespace tktk
{
	class SoundPlayer
	{
	public:

		SoundPlayer(unsigned int soundDataNum);
		~SoundPlayer();

		SoundPlayer(const SoundPlayer& other) = delete;
		SoundPlayer& operator = (const SoundPlayer& other) = delete;

	public:

		void finalize();

		void update();

	public:

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void load(unsigned int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void play(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stop(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pause(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public:

		Sound m_sound;

		// �T�E���h�̃C�x���g�����Ɏg�p����ϐ�
		HANDLE m_soundEvent{ NULL };

		// XAudio�̃|�C���^
		IXAudio2* m_xAudioPtr{ NULL };

		// �}�X�^�����O�{�C�X�̃|�C���^
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_PLAYER_H_

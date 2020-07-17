#ifndef SOUND_H_
#define SOUND_H_

#include <xaudio2.h>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "SoundData.h"

namespace tktk
{
	// �uSoundData�v���Ǘ�����N���X
	class Sound
	{
	public:

		Sound(unsigned int soundDataNum);
		~Sound();

		Sound(const Sound& other) = delete;
		Sound& operator = (const Sound& other) = delete;

	public:

		void update();

	public:

		// �V���ȃT�E���h�����[�h����
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void load(unsigned int id, const std::string& fileName);

		// �S�ẴT�E���h���폜����
		void clear();

		// �w�肵���T�E���h���Đ�����
		void play(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stop(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pause(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	private:

		HeapArray<SoundData> m_assets;

		// �T�E���h�̃C�x���g�����Ɏg�p����ϐ�
		HANDLE m_soundEvent{ NULL };

		// XAudio�̃|�C���^
		IXAudio2* m_xAudioPtr{ NULL };

		// �}�X�^�����O�{�C�X�̃|�C���^
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_H_
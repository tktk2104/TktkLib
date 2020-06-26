#ifndef SOUND_H_
#define SOUND_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SoundData.h"

namespace tktk
{
	// �uSoundData�v���Ǘ�����N���X
	class Sound
	{
	public:

		Sound(unsigned int soundDataNum);
		~Sound() = default;

		Sound(const Sound& other) = delete;
		Sound& operator = (const Sound& other) = delete;

	public:

		// �V���ȃT�E���h�����[�h����
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void load(unsigned int id, const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);

		// �S�ẴT�E���h���폜����
		void clear();

		// �w�肵���T�E���h���Đ�����
		void play(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stop(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pause(unsigned int id);

		// �Đ����̃T�E���h���X�V����
		void updatePlayingSound();

	private:

		HeapArray<SoundData> m_assets;
	};
}
#endif // !SOUND_H_
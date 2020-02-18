#ifndef SOUND_H_
#define SOUND_H_

#include <string>

namespace tktk
{
	// �uSoundManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Sound
	{
	public:

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��ŃT�E���h��ǂݍ��ޏꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		static void load(int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		static void play(int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		static void stop(int id);

		// �w�肵���T�E���h���ꎞ��~����
		static void pause(int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		static void setMasterVolume(float volume);
	};
}
#endif // !SOUND_H_
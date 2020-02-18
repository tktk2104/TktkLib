#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "SoundUpdater.h"

namespace tktk
{
	// �uSoundUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class SoundManager
	{
	public:

		// �uSoundUpdater�v�𐶐�
		static void setUp();

	public:

		// �V�����T�E���h��ǂݍ���
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

	private:

		static CfpPtr<SoundUpdater> m_updater;
	};
}
#endif // !SOUND_MANAGER_H_
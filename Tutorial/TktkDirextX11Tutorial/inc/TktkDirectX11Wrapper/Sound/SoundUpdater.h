#ifndef SOUND_UPDATER_H_
#define SOUND_UPDATER_H_

#include <string>
#include <xaudio2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/SoundAssets.h"

namespace tktk
{
	// �uSoundAssets�v�������Ă���T�E���h���Đ�������~�߂��肷��N���X
	class SoundUpdater
	{
	public:

		SoundUpdater();
		~SoundUpdater();

		SoundUpdater(const SoundUpdater& other) = delete;
		SoundUpdater& operator = (const SoundUpdater& other) = delete;

	public:

		void update();

	public:

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void load(int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void play(int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stop(int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pause(int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public:

		// �T�E���h�A�Z�b�g
		CfpPtr<SoundAssets> m_assets;

		// �T�E���h�̃C�x���g�����Ɏg�p����ϐ�
		HANDLE m_soundEvent{ NULL };

		// XAudio�̃|�C���^
		IXAudio2* m_xAudioPtr{ NULL };

		// �}�X�^�����O�{�C�X�̃|�C���^
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_UPDATER_H_

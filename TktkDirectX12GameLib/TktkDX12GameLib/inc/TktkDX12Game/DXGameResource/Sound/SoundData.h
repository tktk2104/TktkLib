#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

#include <string>
#include <vector>
#include <xaudio2.h>
#include "CSoundCallback.h"

namespace tktk
{
	// �T�E���h���Ǘ�����N���X
	class SoundData
	{
	public:

		SoundData(const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);
		~SoundData();

		SoundData(const SoundData& other) = delete;
		SoundData& operator = (const SoundData& other) = delete;

	public:

		// �T�E���h���Đ����Ă��邩�H
		bool isPlaySound() const;

		// �T�E���h�̍Đ����J�n
		void playSound(bool loopPlay);

		// �T�E���h���Đ����~
		void stopSound();

		// �T�E���h�̍Đ����ꎞ��~
		void pauseSound();

		void update();

	private:

		void loadSound(const std::string& fileName);

		void initSound();

	private:

		// wav�t�@�C���̃n���h��
		HMMIO			m_hmmio{ NULL };
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����MMIO���f�[�^�\��
		MMIOINFO		m_mmioInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���iwav�`�����N�p�j
		MMCKINFO		m_riffChunkInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���i�t�H�[�}�b�g�`�����N�p�j
		MMCKINFO		m_formatChunkInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���i�f�[�^�`�����N�p�j
		MMCKINFO		m_dataChunkInfo;

		// wav�t�@�C���̃t�H�[�}�b�g���
		WAVEFORMATEX	m_wfx;
		// �t�H�[�}�b�g�`�����N���傫�����鎞�Ɏg�p�������
		PCMWAVEFORMAT	m_pcmwf;

		// �T�E���h�̃R�[���o�b�N�����N���X
		CSoundCallback m_cSoundCallback;

		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// �T�E���h�o�b�t�@�̃p�����[�^
		XAUDIO2_BUFFER m_bufinfo;

		// �T�E���h�̏��
		XAUDIO2_VOICE_STATE m_voiceState;

		// �T�E���h�o�b�t�@�̑傫��
		unsigned int m_buflen;

		// �T�E���h�o�b�t�@
		std::vector<unsigned char> m_bufData;

		// �T�E���h�o�b�t�@��ǂݍ��ވʒu
		unsigned char* m_bufLoadPos;

		// �T�E���h�o�b�t�@��ǂݍ��ޒ���
		long m_readlen;

		// �T�E���h�Đ��̏�Ԃ�\���r�b�g�t���O
		unsigned int m_soundPlayState{ 0U };

		// ���y�Đ��p�̃J�E���^
		unsigned int m_soundCount;

		// �T�E���h�o�b�t�@��ǂݍ��񂾑���
		unsigned int m_sumReadlen;
	};
}
#endif // !SOUND_DATA_H_
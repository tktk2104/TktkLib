#ifndef SOUND_ASSETS_H_
#define SOUND_ASSETS_H_

#include <unordered_map>
#include "SoundData.h"

namespace tktk
{
	// �uSoundData�v���Ǘ�����N���X
	class SoundAssets
	{
	public:

		SoundAssets() = default;
		~SoundAssets();

		SoundAssets(const SoundAssets& other) = delete;
		SoundAssets& operator = (const SoundAssets& other) = delete;

	public:

		// �V���ȃT�E���h�����[�h����
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void load(int id, const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);

		// �w�肵���T�E���h���폜����
		void erase(int id);

		// �S�ẴT�E���h���폜����
		void clear();

		// �Đ����̃T�E���h���X�V����
		void updatePlayingSound();

		// �w�肵���T�E���h���Ǘ�����N���X�̃|�C���^���擾
		SoundData* getDataPtr(int id);

	private:

		std::unordered_map<int, SoundData> m_assets;
	};
}
#endif // !SOUND_ASSETS_H_
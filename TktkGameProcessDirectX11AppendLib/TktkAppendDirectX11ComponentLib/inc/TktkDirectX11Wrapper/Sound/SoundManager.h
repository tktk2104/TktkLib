#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// �V�����T�E���h��ǂݍ��ށi�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "SoundId Fraud Type"); }

		// �w�肵���T�E���h���Đ�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void play(IdType id, bool loopPlay)
		{
			playImpl(static_cast<int>(id), loopPlay);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void play(IdType id, bool loopPlay) { static_assert(false, "SoundId Fraud Type"); }

		// �w�肵���T�E���h���~����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void stop(IdType id)
		{
			stopImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void stop(IdType id) { static_assert(false, "SoundId Fraud Type"); }

		// �w�肵���T�E���h���ꎞ��~����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void pause(IdType id)
		{
			pauseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void pause(IdType id) { static_assert(false, "SoundId Fraud Type"); }

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		static void setMasterVolume(float volume);

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, const std::string& fileName);
		static void playImpl(int id, bool loopPlay);
		static void stopImpl(int id);
		static void pauseImpl(int id);

	private:

		static CfpPtr<SoundUpdater> m_updater;
	};
}
#endif // !SOUND_MANAGER_H_
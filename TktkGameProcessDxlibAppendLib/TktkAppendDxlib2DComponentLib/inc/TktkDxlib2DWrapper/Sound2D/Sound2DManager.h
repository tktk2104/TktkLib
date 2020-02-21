#ifndef SOUND_2D_MANAGER_H_
#define SOUND_2D_MANAGER_H_

#include "../Assets/SoundAssets/SoundAssets.h"
#include "SoundPlayType.h"

namespace tktk
{
	class Sound2DManager
	{
	public:

		// �T�E���h���Đ�����
		// �� topPositionFlag �� true �ɂ���ƃT�E���h���ŏ�����Đ�����B
		static void playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag);

		static void stopSound(int id);

		static bool isPlaySound(int id);

		static void changePan(int id, float panPalRate);
		static void changeNextPan(int id, float panPalRate);

		static void changeVolume(int id, float volumeRate);
		static void changeNextVolume(int id, float volumeRate);

		static void setFrequency(int id, int frequencyPalHz);

		static void setLoopPos(int id, float loopTimeSec);

		static void setLoopSamplePos(int id, int loopSamplePosition);

		static void setCurrentPosition(int id, int samplePosition);
	};
}

#endif // !SOUND_2D_MANAGER_H_

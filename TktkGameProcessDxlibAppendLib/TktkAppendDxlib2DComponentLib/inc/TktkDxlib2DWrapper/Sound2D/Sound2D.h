#ifndef SOUND_2D_H_
#define SOUND_2D_H_

#include "SoundPlayType.h"

namespace tktk
{
	class Sound2D
	{
	public:

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
#endif // !SOUND_2D_H_

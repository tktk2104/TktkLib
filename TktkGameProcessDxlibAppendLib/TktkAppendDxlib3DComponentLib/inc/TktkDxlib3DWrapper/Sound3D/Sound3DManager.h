#ifndef SOUND_3D_MANAGER_H_
#define SOUND_3D_MANAGER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkDxlib2DWrapper/Assets/SoundAssets/SoundAssets.h>
#include <TktkDxlib2DWrapper/Sound2D/SoundPlayType.h>

namespace tktk
{
	class Sound3DManager
	{
	public:

		// サウンドを再生する
		// ※ topPositionFlag を true にするとサウンドを最初から再生する。
		static void playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag);

		static void stopSound(int id);

		static bool isPlaySound(int id);

		static void changePlayPosition(int id, const Vector3& playPos);
		static void changeNextPlayPosition(int id, const Vector3& playPos);

		static void changePlayRadius(int id, float playRadius);
		static void changeNextPlayRadius(int id, float playRadius);

		static void changePlayVelocity(int id, const Vector3& velocity);
		static void changeNextPlayVelocity(int id, const Vector3& velocity);

		static void changeVolume(int id, float volumeRate);
		static void changeNextVolume(int id, float volumeRate);

		static void setFrequency(int id, int frequencyPalHz);

		static void setLoopPos(int id, float loopTimeSec);

		static void setLoopSamplePos(int id, int loopSamplePosition);

		static void setCurrentPosition(int id, int samplePosition);

		static void setSoundListenerPosition(const Vector3& pos, const Vector3& front, const Vector3 & up);
	};
}
#endif // !SOUND_3D_MANAGER_H_
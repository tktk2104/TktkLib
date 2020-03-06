#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ElapsedTimer.h"

namespace tktk
{
	class TimeManager
	{
	public:

		static void initialize();

		static void reset();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�
		static float deltaTime();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
		static float noScaleDeltaTime();

		// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
		static float getCurTimeSec();

		// �ő��deltaTime�̒l��ݒ�i���̐��j
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// ���Ԃ̌o�ߑ��x�������擾����
		static float getTimeScale();

		// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
		static void setTimeScale(float timeScaleRate);

		// ��ƂȂ�FPS��ݒ肷��
		static void setBaseFps(int baseFps = 60);

		// ��ƂȂ�FPS���擾����
		static int getBaseFps();

		// �u�ԓI��FPS���擾����
		static float fps();

#ifdef _DEBUG
	private:
		static void tempErrorFunc();
#endif // _DEBUG

	private:

		// ��{�ƂȂ�fps
		static int m_baseFps;

		// �o�ߎ��Ԃ̃^�C�}�[
		static CfpPtr<ElapsedTimer> m_elapsedTimer;
	};
}

#endif // !TIME_MANAGER_H_
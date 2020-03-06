#ifndef ELAPSED_TIMER_H_
#define ELAPSED_TIMER_H_

#include <ctime>

namespace tktk
{
	class ElapsedTimer
	{
	public:

		ElapsedTimer();
		~ElapsedTimer() {}

		ElapsedTimer(const ElapsedTimer& other) = delete;
		ElapsedTimer& operator = (const ElapsedTimer& other) = delete;

	public:

		void reset();

		void frameBegin();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�
		float deltaTime() const;

		// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
		float noScaleDeltaTime() const;

		// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
		float getCurTimeSec();

		// �ő��deltaTime�̒l��ݒ�i���̐��j
		void setMaximumDeltaTime(float maximumDeltaTime);

		// ���Ԃ̌o�ߑ��x�������擾����
		float getTimeScale();

		// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
		void setTimeScale(float timeScaleRate);

		// �u�ԓI��FPS���擾����
		float fps();

	private:

		// �v���O�����̊J�n����
		std::clock_t m_startTime;

		// �O�t���[���̎���
		std::clock_t m_preTime;

		// ���v����
		float m_totalTime;

		// �O�t���[���Ƃ̎��Ԃ̍�
		float m_deltaTime;

		// �ő��deltaTime�̒l
		float m_maximumDeltaTime{ 0.1f };

		// ���Ԃ̌o�ߑ��x����
		float m_timeScaleRate{ 1.0f };
	};
}
#endif // !ELAPSED_TIMER_H_
#include "TktkComponentFramework/Time/TimeManager.h"
#include "TktkComponentFramework/ComponentFrameworkProcessor.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	// ��{�ƂȂ�fps
	int TimeManager::m_baseFps{ 60 };

	// �o�ߎ��Ԃ̃^�C�}�[
	CfpPtr<ElapsedTimer> TimeManager::m_elapsedTimer;

	void TimeManager::initialize()
	{
		m_elapsedTimer = ComponentFrameworkProcessor::createClass<ElapsedTimer>(true);
	}

	void TimeManager::reset()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->reset();
	}

	void TimeManager::update()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->update();
	}

	// �O�t���[���Ƃ̎��Ԃ̍������߂�
	float TimeManager::deltaTime()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->deltaTime();
	}

	// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
	float TimeManager::noScaleDeltaTime()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->noScaleDeltaTime();
	}

	// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
	float TimeManager::getCurTimeSec()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->getCurTimeSec();
	}

	// �ő��deltaTime�̒l��ݒ�i���̐��j
	void TimeManager::setMaximumDeltaTime(float maximumDeltaTime)
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->setMaximumDeltaTime(maximumDeltaTime);
	}

	// ���Ԃ̌o�ߑ��x�������擾����
	float TimeManager::getTimeScale()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->getTimeScale();
	}

	// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
	void TimeManager::setTimeScale(float timeScaleRate)
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		m_elapsedTimer->setTimeScale(timeScaleRate);
	}

	// ��ƂȂ�FPS��ݒ肷��
	void TimeManager::setBaseFps(int baseFps)
	{
		m_baseFps = baseFps;
	}

	// ��ƂȂ�FPS���擾����
	int TimeManager::getBaseFps()
	{
		return m_baseFps;
	}

	// �u�ԓI��FPS���擾����
	float TimeManager::fps()
	{
#ifdef _DEBUG
		tempErrorFunc();
#endif // _DEBUG

		return m_elapsedTimer->fps();
	}

#ifdef _DEBUG
	void TimeManager::tempErrorFunc()
	{
		if (m_elapsedTimer.isNull())
		{
			throw std::runtime_error("not found elapsedTimer");
		}
	}
#endif // _DEBUG
}
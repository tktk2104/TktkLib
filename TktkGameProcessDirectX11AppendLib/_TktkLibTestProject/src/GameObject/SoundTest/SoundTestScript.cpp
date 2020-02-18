#include "SoundTestScript.h"

#include <TktkDirectX11Wrapper/Sound/Sound.h>
#include <TktkDirectX11Wrapper/Sound/SoundManager.h>
#include <TktkDirectX11Wrapper/Input/Keyboard/Keyboard.h>

SoundTestScript::SoundTestScript()
{
}

void SoundTestScript::start()
{
	
}

void SoundTestScript::update()
{
	if (tktk::Keyboard::isTrigger(tktk::KEYBORD_SPACE))
	{
		tktk::Sound::play(1, true);
		tktk::Sound::play(2, true);
	}

	if (tktk::Keyboard::isTrigger(tktk::KEYBORD_RETURN))
	{
		tktk::Sound::stop(1);
	}

	if (tktk::Keyboard::isTrigger(tktk::KEYBORD_LSHIFT))
	{
		tktk::Sound::pause(1);
	}

	if (tktk::Keyboard::isTrigger(tktk::KEYBORD_UP))
	{
		m_masterVolume += 0.1f;

		tktk::Sound::setMasterVolume(m_masterVolume);
	}

	if (tktk::Keyboard::isTrigger(tktk::KEYBORD_DOWN))
	{
		m_masterVolume -= 0.1f;

		tktk::Sound::setMasterVolume(m_masterVolume);
	}
}

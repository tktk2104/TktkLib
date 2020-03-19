#include "TktkAppendDirectX11Component/Graphics/Text/TextDrawerMaker.h"

namespace tktk
{
	TextDrawerMaker TextDrawerMaker::m_self;

	TextDrawerMaker & TextDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = TextDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<TextDrawer> TextDrawerMaker::create()
	{
		return m_user->createComponent<TextDrawer>(
			m_drawPriority,
			m_initText
			);
	}

	TextDrawerMaker & TextDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	TextDrawerMaker & TextDrawerMaker::initText(const std::string & value)
	{
		m_initText = value;
		return *this;
	}


}
#include "TktkAppendDxlib2DComponent/Graphics/PostEffect/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker & PostEffectDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = PostEffectDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		return m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectDrawParameters
			);
	}

	PostEffectDrawerMaker & PostEffectDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	PostEffectDrawerMaker & PostEffectDrawerMaker::postEffectDrawParameters(const std::vector<PostEffectDrawParameter>& value)
	{
		m_postEffectDrawParameters = value;
		return *this;
	}

	PostEffectDrawerMaker & PostEffectDrawerMaker::addPostEffectDrawParameter(const PostEffectDrawParameter & value)
	{
		m_postEffectDrawParameters.push_back(value);
		return *this;
	}
}
#include "TktkAppendDxlib2DComponent/Graphics/PostEffect/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker & PostEffectDrawerMaker::makeStart()
	{
		m_self = PostEffectDrawerMaker();
		return m_self;
	}

	std::shared_ptr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		return std::make_shared<PostEffectDrawer>(
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
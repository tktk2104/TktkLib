#ifndef POST_EFFECT_DRAWER_H_
#define POST_EFFECT_DRAWER_H_

#include <vector>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "PostEffectDrawParameter.h"

namespace tktk
{
	class PostEffectDrawer
		: public ComponentBase
	{
	public:

		PostEffectDrawer(
			float drawPriority,
			const std::vector<PostEffectDrawParameter>& postEffectDrawParameters
		);

	public:

		void draw() const;

	private:

		void drawPostEffect(const PostEffectDrawParameter& parameter) const;

	private:

		std::vector<PostEffectDrawParameter> m_postEffectDrawParameters;
	};
}
#endif // !POST_EFFECT_DRAWER_H_
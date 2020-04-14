#ifndef VIEWPORT_INIT_PARAM_H_
#define VIEWPORT_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct ViewportInitParam
	{
		tktkMath::Vector2	m_windowSize;
		tktkMath::Vector2	m_topLeft;
		float				m_maxDepth;
		float				m_minDepth;
	};
}
#endif // !VIEWPORT_INIT_PARAM_H_
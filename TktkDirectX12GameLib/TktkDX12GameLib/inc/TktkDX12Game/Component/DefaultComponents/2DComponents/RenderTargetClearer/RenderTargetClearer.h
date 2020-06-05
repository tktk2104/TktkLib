#ifndef RENDER_TARGET_CLEARER_H_
#define RENDER_TARGET_CLEARER_H_

#include <TktkMath/Structs/Color.h>
#include "../../../ComponentBase.h"

namespace tktk
{
	class RenderTargetClearer
		: public ComponentBase
	{
	public:

		RenderTargetClearer(unsigned int clearRenderTargetId, const tktkMath::Color& clearColor);

	public:

		void draw() const;

	private:

		unsigned int	m_clearRenderTargetId;
		tktkMath::Color m_clearColor;
	};
}
#endif // !RENDER_TARGET_CLEARER_H_

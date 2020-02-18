#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include <memory>
#include "../../Assets/RenderTargetAssets/RenderTargetAssets.h"

namespace tktk
{
	class RenderTarget
	{
	public:

		static int getMainScreenHandle();

		static void setRenderTarget(int id);

		static void unSetRenderTarget();

		static void drawRenderTargetTexture(int id);
	};
}
#endif // !RENDER_TARGET_H_
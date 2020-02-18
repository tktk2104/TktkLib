#ifndef RENDER_TARGET_MANAGER_H_
#define RENDER_TARGET_MANAGER_H_

#include <memory>
#include "RenderTargetUpdater.h"

namespace tktk
{
	class RenderTargetManager
	{
	public:

		static void setUp();

		static void makeMainScreen(const Vector2& screenSize);

		static int getMainScreenHandle();

		static void setRenderTarget(int id);

		static void unSetRenderTarget();

		static void drawRenderTargetTexture(int id);

	private:

		static std::weak_ptr<RenderTargetUpdater> m_renderTargetUpdater;
	};
}
#endif // !RENDER_TARGET_MANAGER_H_

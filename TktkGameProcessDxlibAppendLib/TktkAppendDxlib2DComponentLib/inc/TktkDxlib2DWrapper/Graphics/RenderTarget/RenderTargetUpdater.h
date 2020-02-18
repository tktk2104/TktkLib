#ifndef RENDER_TARGET_UPDATER_H_
#define RENDER_TARGET_UPDATER_H_

#include <memory>
#include "../../Assets/RenderTargetAssets/RenderTargetAssets.h"

namespace tktk
{
	class RenderTargetUpdater
	{
	public:

		RenderTargetUpdater() = default;

	public:

		void start();
		void onDestroy() const;
		void frameEnd();

	public:

		void makeMainScreen(const Vector2& screenSize);

		int getMainScreenHandle() const;

		void setRenderTarget(int id);

		void unSetRenderTarget();

		void drawRenderTargetTexture(int id);

	private:

		void setDrawScreen(int drawScreenHandle);

	private:

		int m_mainScreenHandle{ -1 };

		std::weak_ptr<RenderTargetAssets> m_renderTargetAssets;
	};
}
#endif // !RENDER_TARGET_UPDATER_H_

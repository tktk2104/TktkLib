#ifndef RENDER_TARGET_ASSETS_H_
#define RENDER_TARGET_ASSETS_H_

#include <string>
#include <unordered_map>
#include <TktkMath/Vector2.h>
#include "RenderTargetHandle.h"

namespace tktk
{
	class RenderTargetAssets
	{
	public:

		RenderTargetAssets() = default;

	public:

		void onDestroy() const;

	public:
		void createRenderTarget(
			int id,
			const Vector2& size,
			bool autoRefresh,
			bool hdr = false,
			bool useZbuffer = false,
			int bitDepth = 32,
			int channel = 4
		);

		void eraseRenderTarget(int id);

		void eraseRenderTargetAll();

		RenderTargetHandle getRenderTargetHandle(int id) const;

		void clearAutoRefreshRenderTargetAll(int mainScreenHandle);

		void clearRenderTarget(int id, int mainScreenHandle);

	private:

		std::unordered_map<int, RenderTargetHandle> m_renderTargetAssetsMap;
	};
}

#endif // !RENDER_TARGET_ASSETS_H_

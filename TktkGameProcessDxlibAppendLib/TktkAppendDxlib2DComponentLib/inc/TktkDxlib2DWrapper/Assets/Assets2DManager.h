#ifndef ASSETS_2D_MANAGER_H_
#define ASSETS_2D_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "SoundAssets/SoundAssets.h"
#include "RenderTargetAssets/RenderTargetAssets.h"
#include "TextureAssets/TextureAssets.h"
#include "MovieAssets/MovieAssets.h"
#include "PixelShaderAssets/PixelShaderAssets.h"

namespace tktk
{
	class Assets2DManager
	{
	public:

		static void createAsset();

		static CfpPtr<SoundAssets> getSoundAssets();

		static CfpPtr<RenderTargetAssets> getRenderTargetAssets();

		static CfpPtr<TextureAssets> getTextureAssets();

		static CfpPtr<MovieAssets> getMovieAssets();

		static CfpPtr<PixelShaderAssets> getPixelShaderAssets();

	private:

		static CfpPtr<SoundAssets>			m_soundAssets;
		static CfpPtr<RenderTargetAssets>	m_renderTargetAssets;
		static CfpPtr<TextureAssets>			m_textureAssets;
		static CfpPtr<MovieAssets>			m_movieAssets;
		static CfpPtr<PixelShaderAssets>		m_pixelShaderAssets;
	};
}
#endif // !ASSETS_2D_MANAGER_H_

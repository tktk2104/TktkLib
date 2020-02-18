#ifndef ASSETS_2D_MANAGER_H_
#define ASSETS_2D_MANAGER_H_

#include <memory>
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

		static std::weak_ptr<SoundAssets> getSoundAssets();

		static std::weak_ptr<RenderTargetAssets> getRenderTargetAssets();

		static std::weak_ptr<TextureAssets> getTextureAssets();

		static std::weak_ptr<MovieAssets> getMovieAssets();

		static std::weak_ptr<PixelShaderAssets> getPixelShaderAssets();

	private:

		static std::weak_ptr<SoundAssets>			m_soundAssets;
		static std::weak_ptr<RenderTargetAssets>	m_renderTargetAssets;
		static std::weak_ptr<TextureAssets>			m_textureAssets;
		static std::weak_ptr<MovieAssets>			m_movieAssets;
		static std::weak_ptr<PixelShaderAssets>		m_pixelShaderAssets;
	};
}
#endif // !ASSETS_2D_MANAGER_H_

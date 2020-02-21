#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<SoundAssets>			Assets2DManager::m_soundAssets;
	CfpPtr<RenderTargetAssets>	Assets2DManager::m_renderTargetAssets;
	CfpPtr<TextureAssets>		Assets2DManager::m_textureAssets;
	CfpPtr<MovieAssets>			Assets2DManager::m_movieAssets;
	CfpPtr<PixelShaderAssets>	Assets2DManager::m_pixelShaderAssets;

	void Assets2DManager::createAsset()
	{
		m_soundAssets			= ComponentFrameworkProcessor::addClass(true, new SoundAssets());
		m_renderTargetAssets	= ComponentFrameworkProcessor::addClass(true, new RenderTargetAssets());
		m_textureAssets			= ComponentFrameworkProcessor::addClass(true, new TextureAssets());
		m_movieAssets			= ComponentFrameworkProcessor::addClass(true, new MovieAssets());
		m_pixelShaderAssets		= ComponentFrameworkProcessor::addClass(true, new PixelShaderAssets());
	}

	CfpPtr<SoundAssets> Assets2DManager::getSoundAssets()
	{
		return m_soundAssets;
	}

	CfpPtr<RenderTargetAssets> Assets2DManager::getRenderTargetAssets()
	{
		return m_renderTargetAssets;
	}

	CfpPtr<TextureAssets> Assets2DManager::getTextureAssets()
	{
		return m_textureAssets;
	}

	CfpPtr<MovieAssets> Assets2DManager::getMovieAssets()
	{
		return m_movieAssets;
	}

	CfpPtr<PixelShaderAssets> Assets2DManager::getPixelShaderAssets()
	{
		return m_pixelShaderAssets;
	}
}
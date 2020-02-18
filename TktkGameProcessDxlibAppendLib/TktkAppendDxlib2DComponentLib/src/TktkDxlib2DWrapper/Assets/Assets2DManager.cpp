#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<SoundAssets>			Assets2DManager::m_soundAssets;
	std::weak_ptr<RenderTargetAssets>	Assets2DManager::m_renderTargetAssets;
	std::weak_ptr<TextureAssets>		Assets2DManager::m_textureAssets;
	std::weak_ptr<MovieAssets>			Assets2DManager::m_movieAssets;
	std::weak_ptr<PixelShaderAssets>	Assets2DManager::m_pixelShaderAssets;

	void Assets2DManager::createAsset()
	{
		auto soundAssets		= std::make_shared<SoundAssets>();
		auto renderTargetAssets = std::make_shared<RenderTargetAssets>();
		auto textureAssets		= std::make_shared<TextureAssets>();
		auto movieAssets		= std::make_shared<MovieAssets>();
		auto pixelShaderAssets	= std::make_shared<PixelShaderAssets>();

		ComponentFrameworkProcessor::addClass(soundAssets);
		ComponentFrameworkProcessor::addClass(renderTargetAssets);
		ComponentFrameworkProcessor::addClass(textureAssets);
		ComponentFrameworkProcessor::addClass(movieAssets);
		ComponentFrameworkProcessor::addClass(pixelShaderAssets);

		m_soundAssets			= soundAssets;
		m_renderTargetAssets	= renderTargetAssets;
		m_textureAssets			= textureAssets;
		m_movieAssets			= movieAssets;
		m_pixelShaderAssets		= pixelShaderAssets;
	}

	std::weak_ptr<SoundAssets> Assets2DManager::getSoundAssets()
	{
		return m_soundAssets;
	}

	std::weak_ptr<RenderTargetAssets> Assets2DManager::getRenderTargetAssets()
	{
		return m_renderTargetAssets;
	}

	std::weak_ptr<TextureAssets> Assets2DManager::getTextureAssets()
	{
		return m_textureAssets;
	}

	std::weak_ptr<MovieAssets> Assets2DManager::getMovieAssets()
	{
		return m_movieAssets;
	}

	std::weak_ptr<PixelShaderAssets> Assets2DManager::getPixelShaderAssets()
	{
		return m_pixelShaderAssets;
	}
}
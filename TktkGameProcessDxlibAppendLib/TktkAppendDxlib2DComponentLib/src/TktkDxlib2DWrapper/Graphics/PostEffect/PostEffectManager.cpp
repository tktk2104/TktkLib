#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<PostEffectUpdater> PostEffectManager::m_postEffectUpdater;

	void PostEffectManager::setUp()
	{
		m_postEffectUpdater = ComponentFrameworkProcessor::addClass(true, new PostEffectUpdater());
	}

	void PostEffectManager::bindPixelShader(int pixelShaderId)
	{
		m_postEffectUpdater->bindPixelShader(pixelShaderId);
	}

	void PostEffectManager::bindRenderTarget(int renderTargetId)
	{
		m_postEffectUpdater->bindRenderTarget(renderTargetId);
	}

	void PostEffectManager::setShaderUsedTexture(int stageIndex, int textureId)
	{
		m_postEffectUpdater->setShaderUsedTexture(stageIndex, textureId);
	}

	void PostEffectManager::clearShaderUsedTexture()
	{
		m_postEffectUpdater->clearShaderUsedTexture();
	}

	void PostEffectManager::setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId)
	{
		m_postEffectUpdater->setShaderUsedRenderTargetTexture(stageIndex, renderTargetsId);
	}

	void PostEffectManager::clearShaderUsedRenderTargetTexture()
	{
		m_postEffectUpdater->clearShaderUsedRenderTargetTexture();
	}

	void PostEffectManager::drawPostEffect()
	{
		m_postEffectUpdater->drawPostEffect();
	}
}
#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<PostEffectUpdater> PostEffectManager::m_postEffectUpdater;

	void PostEffectManager::setUp()
	{
		auto postEffectUpdater = std::make_shared<PostEffectUpdater>();
		ComponentFrameworkProcessor::addClass(postEffectUpdater);
		m_postEffectUpdater = postEffectUpdater;
	}

	void PostEffectManager::bindPixelShader(int pixelShaderId)
	{
		m_postEffectUpdater.lock()->bindPixelShader(pixelShaderId);
	}

	void PostEffectManager::bindRenderTarget(int renderTargetId)
	{
		m_postEffectUpdater.lock()->bindRenderTarget(renderTargetId);
	}

	void PostEffectManager::setShaderUsedTexture(int stageIndex, int textureId)
	{
		m_postEffectUpdater.lock()->setShaderUsedTexture(stageIndex, textureId);
	}

	void PostEffectManager::clearShaderUsedTexture()
	{
		m_postEffectUpdater.lock()->clearShaderUsedTexture();
	}

	void PostEffectManager::setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId)
	{
		m_postEffectUpdater.lock()->setShaderUsedRenderTargetTexture(stageIndex, renderTargetsId);
	}

	void PostEffectManager::clearShaderUsedRenderTargetTexture()
	{
		m_postEffectUpdater.lock()->clearShaderUsedRenderTargetTexture();
	}

	void PostEffectManager::drawPostEffect()
	{
		m_postEffectUpdater.lock()->drawPostEffect();
	}
}
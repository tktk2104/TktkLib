#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffect.h"

#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectManager.h"

namespace tktk
{
	void PostEffect::bindPixelShader(int pixelShaderId)
	{
		PostEffectManager::bindPixelShader(pixelShaderId);
	}

	void PostEffect::bindRenderTarget(int renderTargetId)
	{
		PostEffectManager::bindRenderTarget(renderTargetId);
	}

	void PostEffect::setShaderUsedTexture(int stageIndex, int textureId)
	{
		PostEffectManager::setShaderUsedTexture(stageIndex, textureId);
	}

	void PostEffect::clearShaderUsedTexture()
	{
		PostEffectManager::clearShaderUsedTexture();
	}

	void PostEffect::setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId)
	{
		PostEffectManager::setShaderUsedRenderTargetTexture(stageIndex, renderTargetsId);
	}

	void PostEffect::clearShaderUsedRenderTargetTexture()
	{
		PostEffectManager::clearShaderUsedRenderTargetTexture();
	}

	void PostEffect::drawPostEffect()
	{
		PostEffectManager::drawPostEffect();
	}
}
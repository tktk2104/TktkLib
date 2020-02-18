#include "TktkAppendDxlib2DComponent/Graphics/PostEffect/PostEffectDrawer.h"

#include <algorithm>
#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffect.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTarget.h"

namespace tktk
{
	PostEffectDrawer::PostEffectDrawer(
		float drawPriority,
		const std::vector<PostEffectDrawParameter>& postEffectDrawParameters
	)
		: ComponentBase(drawPriority)
		, m_postEffectDrawParameters(postEffectDrawParameters)
	{
	}

	void PostEffectDrawer::draw() const
	{
		std::for_each(
			std::begin(m_postEffectDrawParameters),
			std::end(m_postEffectDrawParameters),
			[this](const auto& node) { drawPostEffect(node); }
		);
	}

	void PostEffectDrawer::drawPostEffect(const PostEffectDrawParameter & parameter) const
	{
		PostEffect::bindRenderTarget(parameter.drawRenderTargetId);
		PostEffect::bindPixelShader(parameter.usePixelShaderId);

		std::for_each(
			std::begin(parameter.shaderUseTextureIdMap),
			std::end(parameter.shaderUseTextureIdMap),
			[](const auto& node) { PostEffect::setShaderUsedTexture(node.first, node.second); }
		);

		std::for_each(
			std::begin(parameter.shaderUseRenderTargetIdMap),
			std::end(parameter.shaderUseRenderTargetIdMap),
			[](const auto& node) { PostEffect::setShaderUsedRenderTargetTexture(node.first, node.second); }
		);

		RenderTarget::setRenderTarget(parameter.drawRenderTargetId);

		PostEffect::drawPostEffect();

		RenderTarget::unSetRenderTarget();

		PostEffect::clearShaderUsedTexture();
		PostEffect::clearShaderUsedRenderTargetTexture();
	}
}
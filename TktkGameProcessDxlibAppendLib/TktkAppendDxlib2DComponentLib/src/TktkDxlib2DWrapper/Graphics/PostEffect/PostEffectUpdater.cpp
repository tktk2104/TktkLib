#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectUpdater.h"

#include <array>
#include <stdexcept>
#include <algorithm>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"

namespace tktk
{
	void PostEffectUpdater::start()
	{
		auto textureAssets = ComponentFrameworkProcessor::find<TextureAssets>();

		if (textureAssets.expired())
		{
			throw std::runtime_error("PostEffect not found TextureAssets");
		}
		m_textureAssets = textureAssets;

		auto renderTargetAssets = ComponentFrameworkProcessor::find<RenderTargetAssets>();

		if (renderTargetAssets.expired())
		{
			throw std::runtime_error("PostEffect not found RenderTargetAssets");
		}
		m_renderTargetAssets = renderTargetAssets;

		auto pixelShaderAssets = ComponentFrameworkProcessor::find<PixelShaderAssets>();

		if (pixelShaderAssets.expired())
		{
			throw std::runtime_error("PostEffect not found PixelShaderAssets");
		}
		m_pixelShaderAssets = pixelShaderAssets;
	}

	void PostEffectUpdater::bindPixelShader(int pixelShaderId)
	{
		m_pixelShaderId = pixelShaderId;
	}

	void PostEffectUpdater::bindRenderTarget(int renderTargetId)
	{
		m_renderTargetId = renderTargetId;
	}

	void PostEffectUpdater::setShaderUsedTexture(int stageIndex, int textureId)
	{
		m_shaderUsedTextureMap.insert(std::make_pair(stageIndex, textureId));
	}

	void PostEffectUpdater::clearShaderUsedTexture()
	{
		m_shaderUsedTextureMap.clear();
	}

	void PostEffectUpdater::setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId)
	{
		m_shaderUsedRenderTargetMap.insert(std::make_pair(stageIndex, renderTargetsId));
	}

	void PostEffectUpdater::clearShaderUsedRenderTargetTexture()
	{
		m_shaderUsedRenderTargetMap.clear();
	}

	void PostEffectUpdater::drawPostEffect()
	{
		DxLib::MV1SetUseOrigShader(TRUE);
		DxLib::SetUsePixelShader(m_pixelShaderAssets.lock()->getPixelShaderHandle(m_pixelShaderId));

		std::for_each(
			std::begin(m_shaderUsedTextureMap),
			std::end(m_shaderUsedTextureMap),
			[this](const auto & node) { DxLib::SetUseTextureToShader(node.first, m_textureAssets.lock()->getTextureHandles(node.second).textureHandle); }
		);

		std::for_each(
			std::begin(m_shaderUsedRenderTargetMap),
			std::end(m_shaderUsedRenderTargetMap),
			[this](const auto & node) { DxLib::SetUseTextureToShader(node.first, m_renderTargetAssets.lock()->getRenderTargetHandle(node.second).screenGraphHandle); }
		);

		auto renderTargetHandles = m_renderTargetAssets.lock()->getRenderTargetHandle(m_renderTargetId);

		std::array<VERTEX2DSHADER, 4u> vertex2DDatas;

		unsigned int index = 0u;

		std::for_each(
			std::begin(renderTargetHandles.vertices),
			std::end(renderTargetHandles.vertices),
			[&index, &vertex2DDatas](const auto& node) { vertex2DDatas.at(index++) = DXConverter::toVERTEX2DSHADER(node); }
		);

		DxLib::DrawPrimitive2DToShader(
			vertex2DDatas.data(),
			static_cast<int>(vertex2DDatas.size()),
			DX_PRIMTYPE_TRIANGLESTRIP
		);

		DxLib::SetUsePixelShader(-1);
		DxLib::MV1SetUseOrigShader(FALSE);
	}
}
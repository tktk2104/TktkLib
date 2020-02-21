#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectUpdater.h"

#include <array>
#include <stdexcept>
#include <algorithm>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

namespace tktk
{
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
		DxLib::SetUsePixelShader(Assets2DManager::getPixelShaderAssets()->getPixelShaderHandle(m_pixelShaderId));

		std::for_each(
			std::begin(m_shaderUsedTextureMap),
			std::end(m_shaderUsedTextureMap),
			[](const auto & node) { DxLib::SetUseTextureToShader(node.first, Assets2DManager::getTextureAssets()->getTextureHandles(node.second).textureHandle); }
		);

		std::for_each(
			std::begin(m_shaderUsedRenderTargetMap),
			std::end(m_shaderUsedRenderTargetMap),
			[](const auto & node) { DxLib::SetUseTextureToShader(node.first, Assets2DManager::getRenderTargetAssets()->getRenderTargetHandle(node.second).screenGraphHandle); }
		);

		auto renderTargetHandles = Assets2DManager::getRenderTargetAssets()->getRenderTargetHandle(m_renderTargetId);

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
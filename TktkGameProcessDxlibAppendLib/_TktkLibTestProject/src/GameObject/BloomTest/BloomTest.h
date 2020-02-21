#pragma once

#include <array>
#include "CommonIncludePaths.h"

struct BloomTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		auto postEffectDrawParameters = std::vector<tktk::PostEffectDrawParameter>();
		{
			tktk::PostEffectDrawParameter brightPassParam;
			brightPassParam.drawRenderTargetId = RenderTargetId::RENDER_TARGET_BRIGHT_PASS;
			brightPassParam.usePixelShaderId = PixelShaderId::PIXEL_SHADER_BRIGHT_PASS;
			brightPassParam.addShaderUseRenderTargetId(0, RenderTargetId::RENDER_TARGET_BEFOR_BLOOM);
			postEffectDrawParameters.push_back(brightPassParam);
		}

		{
			tktk::PostEffectDrawParameter gaussianBlurHParam;
			gaussianBlurHParam.drawRenderTargetId = RenderTargetId::RENDER_TARGET_BLUR_H;
			gaussianBlurHParam.usePixelShaderId = PixelShaderId::PIXEL_SHADER_GAUSSIAN_BLUR_H;
			gaussianBlurHParam.addShaderUseRenderTargetId(0, RenderTargetId::RENDER_TARGET_BRIGHT_PASS);
			postEffectDrawParameters.push_back(gaussianBlurHParam);
		}

		{
			tktk::PostEffectDrawParameter gaussianBlurVParam;
			gaussianBlurVParam.drawRenderTargetId = RenderTargetId::RENDER_TARGET_BLUR_V;
			gaussianBlurVParam.usePixelShaderId = PixelShaderId::PIXEL_SHADER_GAUSSIAN_BLUR_V;
			gaussianBlurVParam.addShaderUseRenderTargetId(0, RenderTargetId::RENDER_TARGET_BLUR_H);
			postEffectDrawParameters.push_back(gaussianBlurVParam);
		}

		{
			tktk::PostEffectDrawParameter bloomCombineParam;
			bloomCombineParam.drawRenderTargetId = RenderTargetId::RENDER_TARGET_BLOOM_COMBINE;
			bloomCombineParam.usePixelShaderId = PixelShaderId::PIXEL_SHADER_BLOOM_CONBINE;
			bloomCombineParam.addShaderUseRenderTargetId(0, RenderTargetId::RENDER_TARGET_BEFOR_BLOOM);
			bloomCombineParam.addShaderUseRenderTargetId(1, RenderTargetId::RENDER_TARGET_BLUR_V);
			postEffectDrawParameters.push_back(bloomCombineParam);
		}

		gameObject->addComponent(
			tktk::PostEffectDrawerMaker::makeStart()
			.drawPriority(DrawPriority::DRAW_PRIORITY_DEFAULT)
			.postEffectDrawParameters(postEffectDrawParameters)
			.create()
		);
	}
};

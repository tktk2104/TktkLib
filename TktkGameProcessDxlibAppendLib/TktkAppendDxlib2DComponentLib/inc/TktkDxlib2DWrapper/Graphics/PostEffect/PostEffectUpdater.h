#ifndef POST_EFFECT_UPDATER_H_
#define POST_EFFECT_UPDATER_H_

#include <unordered_map>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

#include "../../Assets/TextureAssets/TextureAssets.h"
#include "../../Assets/RenderTargetAssets/RenderTargetAssets.h"
#include "../../Assets/PixelShaderAssets/PixelShaderAssets.h"

namespace tktk
{
	class PostEffectUpdater
	{
	public:

		void bindPixelShader(int pixelShaderId);

		void bindRenderTarget(int renderTargetId);

		void setShaderUsedTexture(int stageIndex, int textureId);
		void clearShaderUsedTexture();

		void setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId);
		void clearShaderUsedRenderTargetTexture();

		// 指定したレンダーターゲットの描画内容に
		// 指定したシェーダーを使用したポストエフェクトをかけて現在の描画先に描画する
		void drawPostEffect();

	private:

		int m_pixelShaderId;
		int m_renderTargetId;
		std::unordered_map<int, int> m_shaderUsedTextureMap;
		std::unordered_map<int, int> m_shaderUsedRenderTargetMap;
	};
}

#endif // !POST_EFFECT_UPDATER_H_

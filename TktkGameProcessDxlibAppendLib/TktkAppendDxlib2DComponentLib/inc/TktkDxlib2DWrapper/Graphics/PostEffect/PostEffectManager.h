#ifndef POST_EFFECT_MANAGER_H_
#define POST_EFFECT_MANAGER_H_

#include <memory>
#include "PostEffectUpdater.h"

namespace tktk
{
	class PostEffectManager
	{
	public:

		static void setUp();

		static void bindPixelShader(int pixelShaderId);

		static void bindRenderTarget(int renderTargetId);

		static void setShaderUsedTexture(int stageIndex, int textureId);
		static void clearShaderUsedTexture();

		static void setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId);
		static void clearShaderUsedRenderTargetTexture();

		// 指定したレンダーターゲットの描画内容に
		// 指定したシェーダーを使用したポストエフェクトをかけて現在の描画先に描画する
		static void drawPostEffect();

	private:

		static std::weak_ptr<PostEffectUpdater> m_postEffectUpdater;
	};
}
#endif // !POST_EFFECT_MANAGER_H_

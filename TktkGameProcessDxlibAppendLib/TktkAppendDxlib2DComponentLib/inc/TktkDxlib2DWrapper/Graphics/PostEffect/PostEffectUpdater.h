#ifndef POST_EFFECT_UPDATER_H_
#define POST_EFFECT_UPDATER_H_

#include <memory>
#include <unordered_map>

#include "../../Assets/TextureAssets/TextureAssets.h"
#include "../../Assets/RenderTargetAssets/RenderTargetAssets.h"
#include "../../Assets/PixelShaderAssets/PixelShaderAssets.h"

namespace tktk
{
	class PostEffectUpdater
	{
	public:

		void start();

	public:

		void bindPixelShader(int pixelShaderId);

		void bindRenderTarget(int renderTargetId);

		void setShaderUsedTexture(int stageIndex, int textureId);
		void clearShaderUsedTexture();

		void setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId);
		void clearShaderUsedRenderTargetTexture();

		// �w�肵�������_�[�^�[�Q�b�g�̕`����e��
		// �w�肵���V�F�[�_�[���g�p�����|�X�g�G�t�F�N�g�������Č��݂̕`���ɕ`�悷��
		void drawPostEffect();

	private:

		int m_pixelShaderId;
		int m_renderTargetId;
		std::unordered_map<int, int> m_shaderUsedTextureMap;
		std::unordered_map<int, int> m_shaderUsedRenderTargetMap;

		std::weak_ptr<TextureAssets> m_textureAssets;
		std::weak_ptr<RenderTargetAssets> m_renderTargetAssets;
		std::weak_ptr<PixelShaderAssets> m_pixelShaderAssets;
	};
}

#endif // !POST_EFFECT_UPDATER_H_

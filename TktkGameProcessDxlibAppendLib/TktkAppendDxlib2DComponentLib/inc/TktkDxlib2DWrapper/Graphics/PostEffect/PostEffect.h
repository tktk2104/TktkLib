#ifndef POST_EFFECT_H_
#define POST_EFFECT_H_

namespace tktk
{
	class PostEffect
	{
	public:

		static void bindPixelShader(int pixelShaderId);

		static void bindRenderTarget(int renderTargetId);

		static void setShaderUsedTexture(int stageIndex, int textureId);
		static void clearShaderUsedTexture();

		static void setShaderUsedRenderTargetTexture(int stageIndex, int renderTargetsId);
		static void clearShaderUsedRenderTargetTexture();

		// �w�肵�������_�[�^�[�Q�b�g�̕`����e��
		// �w�肵���V�F�[�_�[���g�p�����|�X�g�G�t�F�N�g�������Č��݂̕`���ɕ`�悷��
		static void drawPostEffect();
	};
}
#endif // !POST_EFFECT_H_
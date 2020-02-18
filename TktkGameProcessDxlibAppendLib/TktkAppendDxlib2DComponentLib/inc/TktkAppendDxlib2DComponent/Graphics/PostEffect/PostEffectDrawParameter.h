#ifndef POST_EFFECT_DRAW_PARAMETER_H_
#define POST_EFFECT_DRAW_PARAMETER_H_

#include <unordered_map>

namespace tktk
{
	struct PostEffectDrawParameter
	{
	public:

		void addShaderUseTextureId(int stageIndex, int textureId);

		void addShaderUseRenderTargetId(int stageIndex, int renderTargetsId);

	public:

		int drawRenderTargetId{ -1 };

		int usePixelShaderId{ -1 };

		std::unordered_map<int, int> shaderUseTextureIdMap;

		std::unordered_map<int, int> shaderUseRenderTargetIdMap;
	};
}
#endif // !POST_EFFECT_DRAW_PARAMETER_H_
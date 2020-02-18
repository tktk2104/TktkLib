#include "TktkAppendDxlib2DComponent/Graphics/PostEffect/PostEffectDrawParameter.h"

namespace tktk
{
	void PostEffectDrawParameter::addShaderUseTextureId(int stageIndex, int textureId)
	{
		shaderUseTextureIdMap.insert(std::make_pair(stageIndex, textureId));
	}

	void PostEffectDrawParameter::addShaderUseRenderTargetId(int stageIndex, int renderTargetsId)
	{
		shaderUseRenderTargetIdMap.insert(std::make_pair(stageIndex, renderTargetsId));
	}
}
#ifndef DX_GAME_RESOURCE_INIT_PARAM_H_
#define DX_GAME_RESOURCE_INIT_PARAM_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	struct DXGameResourceInitParam
	{
		tktk::ShaderFilePaths		spriteShaderFilePaths;
		tktk::ShaderFilePaths		basicMeshShaderFilePaths;
		PostEffectShaderFilePaths	postEffectShaderFilePaths;

		unsigned int spriteNum;
		unsigned int basicMeshNum;
		unsigned int basicMeshMaterialNum;
		unsigned int postEffectMaterialNum;
	};
}
#endif // !DX_GAME_RESOURCE_INIT_PARAM_H_
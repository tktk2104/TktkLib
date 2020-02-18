#ifndef SHADER_USE_CONSTANT_BUFFER_H_
#define SHADER_USE_CONSTANT_BUFFER_H_

#include "ShaderType.h"

namespace tktk
{
	struct ShaderUseConstantBuffer
	{
		ShaderType targetShaderType;
		int shaderConstantBufferHandle;
	};
}
#endif // !SHADER_USE_CONSTANT_BUFFER_H_
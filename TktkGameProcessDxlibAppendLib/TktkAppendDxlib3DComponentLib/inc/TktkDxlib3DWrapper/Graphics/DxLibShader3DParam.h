#ifndef DXLIB_SHADER_3D_PARAM_H_
#define DXLIB_SHADER_3D_PARAM_H_

#include <unordered_map>
#include "ShaderUseConstantBuffer.h"
#include "ShaderUseGraphHandle.h"

namespace tktk
{
	struct DxLibShader3DParam
	{
		void clearShaderUseConstantBuffer();
		void addShaderUseConstantBuffer(int slot, ShaderType targetShaderType, int id);
		void clearShaderUseGraphHandleMap();
		void addShaderUseTexture(int stageIndex, int id, int texAddress);
		void addShaderUseModelTexture(int stageIndex, int id, int texAddress);
		void addShaderUseRenderTarget(int stageIndex, int id, int texAddress);
		bool useOriginalShader() const;

		int pixelShaderId{ -1 };
		int vertexShaderId{ -1 };
		int vertexBufferId{ -1 };
		std::unordered_map<int, ShaderUseConstantBuffer> shaderUseConstantBufferMap;
		std::unordered_map<int, ShaderUseGraphHandle> shaderUseGraphHandleMap;
	};
}
#endif // !DXLIB_SHADER_3D_PARAM_H_

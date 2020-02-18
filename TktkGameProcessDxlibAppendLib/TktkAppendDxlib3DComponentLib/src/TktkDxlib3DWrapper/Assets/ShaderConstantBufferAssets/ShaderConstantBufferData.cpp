#include "TktkDxlib3DWrapper/Assets/ShaderConstantBufferAssets/ShaderConstantBufferData.h"

namespace tktk
{
	ShaderConstantBufferData::ShaderConstantBufferData(
		int shaderConstantBufferHandle, 
		std::type_index shaderConstantBufferType
	)
		: shaderConstantBufferHandle(shaderConstantBufferHandle)
		, shaderConstantBufferType(shaderConstantBufferType)
	{
	}
}
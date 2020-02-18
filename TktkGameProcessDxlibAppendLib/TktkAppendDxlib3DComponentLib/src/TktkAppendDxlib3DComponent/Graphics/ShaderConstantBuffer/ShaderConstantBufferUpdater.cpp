#include "TktkAppendDxlib3DComponent/Graphics/ShaderConstantBuffer/ShaderConstantBufferUpdater.h"

#include <DxLib.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

namespace tktk
{
	ShaderConstantBufferUpdater::ShaderConstantBufferUpdater(int shaderConstantBufferId)
		: m_shaderConstantBufferId(shaderConstantBufferId)
	{
	}

	void * ShaderConstantBufferUpdater::getRawBufferData(int constantBufferHandle)
	{
		return DxLib::GetBufferShaderConstantBuffer(constantBufferHandle);
	}
}
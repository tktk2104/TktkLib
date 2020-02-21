#include "TktkAppendDxlib3DComponent/Graphics/ShaderConstantBuffer/ShaderConstantBufferUpdaterMaker.h"

namespace tktk
{
	ShaderConstantBufferUpdaterMaker ShaderConstantBufferUpdaterMaker::m_self;

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::makeStart()
	{
		m_self = ShaderConstantBufferUpdaterMaker();
		return m_self;
	}

	ShaderConstantBufferUpdater* ShaderConstantBufferUpdaterMaker::create()
	{
		return new ShaderConstantBufferUpdater(
			m_shaderConstantBufferId
			);
	}

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::shaderConstantBufferId(int value)
	{
		m_shaderConstantBufferId = value;
		return *this;
	}
}
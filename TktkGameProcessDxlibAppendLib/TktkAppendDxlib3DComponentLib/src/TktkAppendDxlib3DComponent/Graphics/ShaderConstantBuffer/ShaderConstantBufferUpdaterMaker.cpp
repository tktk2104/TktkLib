#include "TktkAppendDxlib3DComponent/Graphics/ShaderConstantBuffer/ShaderConstantBufferUpdaterMaker.h"

namespace tktk
{
	ShaderConstantBufferUpdaterMaker ShaderConstantBufferUpdaterMaker::m_self;

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::makeStart()
	{
		m_self = ShaderConstantBufferUpdaterMaker();
		return m_self;
	}

	std::shared_ptr<ShaderConstantBufferUpdater> ShaderConstantBufferUpdaterMaker::create()
	{
		return std::make_shared<ShaderConstantBufferUpdater>(
			m_shaderConstantBufferId
			);
	}

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::shaderConstantBufferId(int value)
	{
		m_shaderConstantBufferId = value;
		return *this;
	}
}
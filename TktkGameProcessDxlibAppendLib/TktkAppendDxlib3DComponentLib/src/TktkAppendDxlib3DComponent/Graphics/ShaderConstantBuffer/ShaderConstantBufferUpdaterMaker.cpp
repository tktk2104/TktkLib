#include "TktkAppendDxlib3DComponent/Graphics/ShaderConstantBuffer/ShaderConstantBufferUpdaterMaker.h"

namespace tktk
{
	ShaderConstantBufferUpdaterMaker ShaderConstantBufferUpdaterMaker::m_self;

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::makeStart(GameObjectPtr user)
	{
		m_self = ShaderConstantBufferUpdaterMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<ShaderConstantBufferUpdater> ShaderConstantBufferUpdaterMaker::create()
	{
		return m_user->createComponent<ShaderConstantBufferUpdater>(
			m_shaderConstantBufferId
			);
	}

	ShaderConstantBufferUpdaterMaker & ShaderConstantBufferUpdaterMaker::shaderConstantBufferId(int value)
	{
		m_shaderConstantBufferId = value;
		return *this;
	}
}
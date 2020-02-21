#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<LightAssets>					Assets3DManager::m_lightAssets;
	CfpPtr<ShadowMapAssets>				Assets3DManager::m_shadowMapAssets;
	CfpPtr<MeshAssets>					Assets3DManager::m_meshAssets;
	CfpPtr<MeshTextureAssets>			Assets3DManager::m_meshTextureAssets;
	CfpPtr<VertexShaderAssets>			Assets3DManager::m_vertexShaderAssets;
	CfpPtr<ShaderConstantBufferAssets>	Assets3DManager::m_shaderConstantBufferAssets;

	void Assets3DManager::createAsset()
	{
		m_lightAssets					= ComponentFrameworkProcessor::addClass(true, new LightAssets());
		m_shadowMapAssets				= ComponentFrameworkProcessor::addClass(true, new ShadowMapAssets());
		m_meshAssets					= ComponentFrameworkProcessor::addClass(true, new MeshAssets());
		m_meshTextureAssets				= ComponentFrameworkProcessor::addClass(true, new MeshTextureAssets());
		m_vertexShaderAssets			= ComponentFrameworkProcessor::addClass(true, new VertexShaderAssets());
		m_shaderConstantBufferAssets	= ComponentFrameworkProcessor::addClass(true, new ShaderConstantBufferAssets());
	}

	CfpPtr<LightAssets> Assets3DManager::getLightAssets()
	{
		return m_lightAssets;
	}

	CfpPtr<ShadowMapAssets> Assets3DManager::getShadowMapAssets()
	{
		return m_shadowMapAssets;
	}

	CfpPtr<MeshAssets> Assets3DManager::getMeshAssets()
	{
		return m_meshAssets;
	}

	CfpPtr<MeshTextureAssets> Assets3DManager::getMeshTextureAssets()
	{
		return m_meshTextureAssets;
	}

	CfpPtr<VertexShaderAssets> Assets3DManager::getVertexShaderAssets()
	{
		return m_vertexShaderAssets;
	}

	CfpPtr<ShaderConstantBufferAssets> Assets3DManager::getShaderConstantBufferAssets()
	{
		return m_shaderConstantBufferAssets;
	}
}
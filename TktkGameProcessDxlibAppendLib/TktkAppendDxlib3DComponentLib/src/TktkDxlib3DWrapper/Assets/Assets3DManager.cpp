#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<LightAssets>			Assets3DManager::m_lightAssets;
	std::weak_ptr<ShadowMapAssets>		Assets3DManager::m_shadowMapAssets;
	std::weak_ptr<MeshAssets>			Assets3DManager::m_meshAssets;
	std::weak_ptr<MeshTextureAssets>	Assets3DManager::m_meshTextureAssets;
	std::weak_ptr<VertexShaderAssets>	Assets3DManager::m_vertexShaderAssets;
	std::weak_ptr<ShaderConstantBufferAssets>	Assets3DManager::m_shaderConstantBufferAssets;

	void Assets3DManager::createAsset()
	{
		auto lightAssets				= std::make_shared<LightAssets>();
		auto shadowMapAssets			= std::make_shared<ShadowMapAssets>();
		auto meshAssets					= std::make_shared<MeshAssets>();
		auto meshTextureAssets			= std::make_shared<MeshTextureAssets>();
		auto vertexShaderAssets			= std::make_shared<VertexShaderAssets>();
		auto shaderConstantBufferAssets = std::make_shared<ShaderConstantBufferAssets>();

		ComponentFrameworkProcessor::addClass(lightAssets);
		ComponentFrameworkProcessor::addClass(shadowMapAssets);
		ComponentFrameworkProcessor::addClass(meshAssets);
		ComponentFrameworkProcessor::addClass(meshTextureAssets);
		ComponentFrameworkProcessor::addClass(vertexShaderAssets);
		ComponentFrameworkProcessor::addClass(shaderConstantBufferAssets);

		m_lightAssets					= lightAssets;
		m_shadowMapAssets				= shadowMapAssets;
		m_meshAssets					= meshAssets;
		m_meshTextureAssets				= meshTextureAssets;
		m_vertexShaderAssets			= vertexShaderAssets;
		m_shaderConstantBufferAssets	= shaderConstantBufferAssets;
	}

	std::weak_ptr<LightAssets> Assets3DManager::getLightAssets()
	{
		return m_lightAssets;
	}

	std::weak_ptr<ShadowMapAssets> Assets3DManager::getShadowMapAssets()
	{
		return m_shadowMapAssets;
	}

	std::weak_ptr<MeshAssets> Assets3DManager::getMeshAssets()
	{
		return m_meshAssets;
	}

	std::weak_ptr<MeshTextureAssets> Assets3DManager::getMeshTextureAssets()
	{
		return m_meshTextureAssets;
	}

	std::weak_ptr<VertexShaderAssets> Assets3DManager::getVertexShaderAssets()
	{
		return m_vertexShaderAssets;
	}

	std::weak_ptr<ShaderConstantBufferAssets> Assets3DManager::getShaderConstantBufferAssets()
	{
		return m_shaderConstantBufferAssets;
	}
}
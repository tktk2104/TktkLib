#ifndef ASSETS_3D_MANAGER_H_
#define ASSETS_3D_MANAGER_H_

#include <memory>
#include "LightAssets/LightAssets.h"
#include "ShadowMapAssets/ShadowMapAssets.h"
#include "MeshAssets/MeshAssets.h"
#include "MeshTextureAssets/MeshTextureAssets.h"
#include "VertexShaderAssets/VertexShaderAssets.h"
#include "ShaderConstantBufferAssets/ShaderConstantBufferAssets.h"

namespace tktk
{
	class Assets3DManager
	{
	public:

		static void createAsset();

		static std::weak_ptr<LightAssets> getLightAssets();
		static std::weak_ptr<ShadowMapAssets> getShadowMapAssets();
		static std::weak_ptr<MeshAssets> getMeshAssets();
		static std::weak_ptr<MeshTextureAssets> getMeshTextureAssets();
		static std::weak_ptr<VertexShaderAssets> getVertexShaderAssets();
		static std::weak_ptr<ShaderConstantBufferAssets> getShaderConstantBufferAssets();

	private:

		static std::weak_ptr<LightAssets>			m_lightAssets;
		static std::weak_ptr<ShadowMapAssets>		m_shadowMapAssets;
		static std::weak_ptr<MeshAssets>			m_meshAssets;
		static std::weak_ptr<MeshTextureAssets>		m_meshTextureAssets;
		static std::weak_ptr<VertexShaderAssets>	m_vertexShaderAssets;
		static std::weak_ptr<ShaderConstantBufferAssets>	m_shaderConstantBufferAssets;
	};
}
#endif // !ASSETS_3D_MANAGER_H_
#ifndef ASSETS_3D_MANAGER_H_
#define ASSETS_3D_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
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

		static CfpPtr<LightAssets>					getLightAssets();
		static CfpPtr<ShadowMapAssets>				getShadowMapAssets();
		static CfpPtr<MeshAssets>					getMeshAssets();
		static CfpPtr<MeshTextureAssets>			getMeshTextureAssets();
		static CfpPtr<VertexShaderAssets>			getVertexShaderAssets();
		static CfpPtr<ShaderConstantBufferAssets>	getShaderConstantBufferAssets();

	private:

		static CfpPtr<LightAssets>					m_lightAssets;
		static CfpPtr<ShadowMapAssets>				m_shadowMapAssets;
		static CfpPtr<MeshAssets>					m_meshAssets;
		static CfpPtr<MeshTextureAssets>			m_meshTextureAssets;
		static CfpPtr<VertexShaderAssets>			m_vertexShaderAssets;
		static CfpPtr<ShaderConstantBufferAssets>	m_shaderConstantBufferAssets;
	};
}
#endif // !ASSETS_3D_MANAGER_H_
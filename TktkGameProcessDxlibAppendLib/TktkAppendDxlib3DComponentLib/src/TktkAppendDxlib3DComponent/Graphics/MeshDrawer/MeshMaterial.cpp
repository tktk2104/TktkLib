#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshMaterial.h"

namespace tktk
{
	MeshMaterial::MeshMaterial(const DxLibShader3DParam & dxLibShader3DParam)
		: m_dxLibShader3DParam(dxLibShader3DParam)
	{
	}

	const DxLibShader3DParam & MeshMaterial::getDxLibShader3DParam() const
	{
		return m_dxLibShader3DParam;
	}

	void MeshMaterial::useOrigShader(int pixelShaderId, int vertexShaderId)
	{
		m_dxLibShader3DParam.pixelShaderId = pixelShaderId;
		m_dxLibShader3DParam.vertexShaderId = vertexShaderId;
	}

	void MeshMaterial::unUseOrigShader()
	{
		m_dxLibShader3DParam.pixelShaderId = -1;
		m_dxLibShader3DParam.vertexShaderId = -1;
	}

	void MeshMaterial::clearShaderUseConstantBuffer()
	{
		m_dxLibShader3DParam.clearShaderUseConstantBuffer();
	}

	void MeshMaterial::setShaderUseConstantBuffer(int slot, ShaderType targetShaderType, int shaderConstantBufferId)
	{
		m_dxLibShader3DParam.addShaderUseConstantBuffer(slot, targetShaderType, shaderConstantBufferId);
	}

	void MeshMaterial::clearShaderUseGraphHandleMap()
	{
		m_dxLibShader3DParam.clearShaderUseGraphHandleMap();
	}

	void MeshMaterial::addShaderUsedTexture(int stageIndex, int textureId, ShaderUseTextureAddressType addressType)
	{
		m_dxLibShader3DParam.addShaderUseTexture(stageIndex, textureId, addressType);
	}

	void MeshMaterial::addShaderUsedModelTexture(int stageIndex, int modelTextureId, ShaderUseTextureAddressType addressType)
	{
		m_dxLibShader3DParam.addShaderUseModelTexture(stageIndex, modelTextureId, addressType);
	}

	void MeshMaterial::addShaderUsedRenderTarget(int stageIndex, int renderTargetId, ShaderUseTextureAddressType addressType)
	{
		m_dxLibShader3DParam.addShaderUseRenderTarget(stageIndex, renderTargetId, addressType);
	}
}
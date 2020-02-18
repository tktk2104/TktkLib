#include "TktkDxlib3DWrapper/Graphics/DxLibShader3DParam.h"

#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

namespace tktk
{
	void DxLibShader3DParam::clearShaderUseConstantBuffer()
	{
		shaderUseConstantBufferMap.clear();
	}

	void DxLibShader3DParam::addShaderUseConstantBuffer(int slot, ShaderType targetShaderType, int id)
	{
		ShaderUseConstantBuffer shaderUseConstantBuffer;
		shaderUseConstantBuffer.targetShaderType = targetShaderType;
		shaderUseConstantBuffer.shaderConstantBufferHandle = Assets3DManager::getShaderConstantBufferAssets().lock()->getData(id).shaderConstantBufferHandle;

		shaderUseConstantBufferMap.insert(std::make_pair(slot, shaderUseConstantBuffer));
	}

	void DxLibShader3DParam::clearShaderUseGraphHandleMap()
	{
		shaderUseGraphHandleMap.clear();
	}

	void DxLibShader3DParam::addShaderUseTexture(int stageIndex, int id, int texAddress)
	{
		ShaderUseGraphHandle shaderUseGraphHandle;
		shaderUseGraphHandle.texAddress = texAddress;
		shaderUseGraphHandle.graphHandle = Assets2DManager::getTextureAssets().lock()->getTextureHandles(id).textureHandle;

		shaderUseGraphHandleMap.insert(std::make_pair(stageIndex, shaderUseGraphHandle));
	}

	void DxLibShader3DParam::addShaderUseModelTexture(int stageIndex, int id, int texAddress)
	{
		ShaderUseGraphHandle shaderUseGraphHandle;
		shaderUseGraphHandle.texAddress = texAddress;
		shaderUseGraphHandle.graphHandle = Assets3DManager::getMeshTextureAssets().lock()->getMeshTextureHandles(id);

		shaderUseGraphHandleMap.insert(std::make_pair(stageIndex, shaderUseGraphHandle));
	}

	void DxLibShader3DParam::addShaderUseRenderTarget(int stageIndex, int id, int texAddress)
	{
		ShaderUseGraphHandle shaderUseGraphHandle;
		shaderUseGraphHandle.texAddress = texAddress;
		shaderUseGraphHandle.graphHandle = Assets2DManager::getRenderTargetAssets().lock()->getRenderTargetHandle(id).screenGraphHandle;

		shaderUseGraphHandleMap.insert(std::make_pair(stageIndex, shaderUseGraphHandle));
	}

	bool DxLibShader3DParam::useOriginalShader() const
	{
		return (pixelShaderId != -1 && vertexShaderId != -1);
	}
}
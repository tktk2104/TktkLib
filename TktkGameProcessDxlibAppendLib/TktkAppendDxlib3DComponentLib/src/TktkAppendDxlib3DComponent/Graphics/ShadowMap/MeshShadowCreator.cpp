#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/MeshShadowCreator.h"
#include <stdexcept>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

namespace tktk
{
	inline void setShaderTexture(int stageIndex, int texAddress, int graphHandle);

	MeshShadowCreator::MeshShadowCreator(
		float drawPriority,
		CfpPtr<MeshDrawer> meshDrawer
	)
		: ComponentBase(drawPriority)
		, m_meshDrawer(meshDrawer)
	{
	}

	void MeshShadowCreator::draw() const
	{
		//if (m_meshDrawer.isNull() || !m_meshDrawer->isActive()) return;
		//
		//int meshID = m_meshDrawer->getMeshID();
		//auto localBoneMatrices = m_meshDrawer->getLocalBoneMatrices();
		//auto dxLibDraw3DParam = m_meshDrawer->getDxLibDraw3DParam();
		//auto dxLibShader3DParam = m_meshDrawer->getDxLibShader3DParam();
		//auto transform3D = m_meshDrawer->getComponent<Transform3D>();
		//
		//if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(dxLibDraw3DParam.renderTargetId);
		//
		//if (dxLibShader3DParam.useOriginalShader())
		//{
		//	DxLib::MV1SetUseOrigShader(TRUE);
		//
		//	auto pixelShaderAssets = Assets2DManager::getPixelShaderAssets();
		//	auto vertexShaderAssets = Assets3DManager::getVertexShaderAssets();
		//
		//	DxLib::SetUseVertexShader(pixelShaderAssets->getPixelShaderHandle(dxLibShader3DParam.pixelShaderId));
		//	DxLib::SetUsePixelShader(vertexShaderAssets->getVertexShaderHandle(dxLibShader3DParam.vertexShaderId));
		//
		//	std::for_each(
		//		std::begin(dxLibShader3DParam.shaderUseGraphHandleMap),
		//		std::end(dxLibShader3DParam.shaderUseGraphHandleMap),
		//		[](const auto& node) { setShaderTexture(node.first, node.second.texAddress, node.second.graphHandle); }
		//	);
		//}
		//
		//int drawMeshHandle = Assets3DManager::getMeshAssets()->getMeshHandle(meshID).meshHandle;
		//
		//for (int i = 0; i < static_cast<int>(localBoneMatrices.size()); ++i)
		//{
		//	DxLib::MV1SetFrameUserLocalMatrix(drawMeshHandle, i, DXConverter::toMATRIX(localBoneMatrices.at(i)));
		//}
		//
		//DxLib::SetDrawBlendMode(dxLibDraw3DParam.blendMode, static_cast<int>(dxLibDraw3DParam.blendParam));
		//DxLib::SetUseLighting((dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		//DxLib::MV1SetWriteZBuffer(drawMeshHandle, (dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		//DxLib::MV1SetMatrix(drawMeshHandle, DXConverter::toMATRIX(dxLibDraw3DParam.localMat * transform3D->calculateWorldMatrix()));
		//DxLib::MV1DrawModel(drawMeshHandle);
		//
		//if (dxLibShader3DParam.useOriginalShader()) DxLib::MV1SetUseOrigShader(FALSE);
		//
		//if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	void setShaderTexture(int stageIndex, int texAddress, int graphHandle)
	{
		DxLib::SetTextureAddressMode(texAddress, stageIndex);
		DxLib::SetUseTextureToShader(stageIndex, graphHandle);
	}
}
#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshDrawer.h"

#include <stdexcept>
#include <algorithm>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/MeshShadowCreator.h"

namespace tktk
{
	inline void setConstantBuffer(int slot, ShaderType targetShaderType, int shaderConstantBufferHandle);
	inline void setShaderTexture(int stageIndex, int texAddress, int graphHandle);

	MeshDrawer::MeshDrawer(
		const DxLibDraw3DParam& dxLibDraw3DParam,
		int meshID
	)
		: ComponentBase(dxLibDraw3DParam.drawPriority)
		, m_dxLibDraw3DParam(dxLibDraw3DParam)
		, m_meshID(meshID)
	{
	}

	void MeshDrawer::awake()
	{
	}

	void MeshDrawer::start()
	{
		if (m_dxLibDraw3DParam.createShadow)
		{
			getGameObject()->addComponent(new MeshShadowCreator(
				m_dxLibDraw3DParam.shadowCreatorPriority,
				getThisPtr<MeshDrawer>()
				));
		}

		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.isNull())
		{
			throw std::runtime_error("MeshDrawer not found Transform3D");
		}

		m_meshMaterial = getComponent<MeshMaterial>();

		MeshHandles drawMeshHandles = Assets3DManager::getMeshAssets()->getMeshHandle(m_meshID);
		m_localBoneMatrices = std::vector<Matrix4>(DxLib::MV1GetFrameNum(drawMeshHandles.meshHandle), Matrix4::identity);
		for (int i = 0; i < static_cast<int>(m_localBoneMatrices.size()); ++i)
		{
			DxLib::MV1ResetFrameUserLocalMatrix(drawMeshHandles.meshHandle, i);
			m_localBoneMatrices.at(i) = DXConverter::toMatrix(DxLib::MV1GetFrameLocalMatrix(drawMeshHandles.meshHandle, i));
		}
	}

	void MeshDrawer::draw() const
	{
		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(m_dxLibDraw3DParam.renderTargetId);

		if (!m_meshMaterial.isNull() && m_meshMaterial->getDxLibShader3DParam().useOriginalShader())
		{
			const DxLibShader3DParam& shaderParam = m_meshMaterial->getDxLibShader3DParam();

			DxLib::MV1SetUseOrigShader(TRUE);

			auto pixelShaderAssets = Assets2DManager::getPixelShaderAssets();
			auto vertexShaderAssets = Assets3DManager::getVertexShaderAssets();

			DxLib::SetUseVertexShader(pixelShaderAssets->getPixelShaderHandle(shaderParam.pixelShaderId));
			DxLib::SetUsePixelShader(vertexShaderAssets->getVertexShaderHandle(shaderParam.vertexShaderId));

			std::for_each(
				std::begin(shaderParam.shaderUseConstantBufferMap),
				std::end(shaderParam.shaderUseConstantBufferMap),
				[](const auto& node) { setConstantBuffer(node.first, node.second.targetShaderType, node.second.shaderConstantBufferHandle); }
			);

			std::for_each(
				std::begin(shaderParam.shaderUseGraphHandleMap),
				std::end(shaderParam.shaderUseGraphHandleMap),
				[](const auto& node) { setShaderTexture(node.first, node.second.texAddress, node.second.graphHandle); }
			);
		}

		int drawMeshHandle = Assets3DManager::getMeshAssets()->getMeshHandle(m_meshID).meshHandle;

		for (int i = 0; i < static_cast<int>(m_localBoneMatrices.size()); ++i)
		{
			DxLib::MV1SetFrameUserLocalMatrix(drawMeshHandle, i, DXConverter::toMATRIX(m_localBoneMatrices.at(i)));
		}

		DxLib::SetDrawBlendMode(m_dxLibDraw3DParam.blendMode, static_cast<int>(m_dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((m_dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::MV1SetWriteZBuffer(drawMeshHandle, (m_dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DxLib::MV1SetMatrix(drawMeshHandle, DXConverter::toMATRIX(m_dxLibDraw3DParam.localMat * m_transform3D->calculateWorldMatrix()));
		DxLib::MV1DrawModel(drawMeshHandle);

		if (!m_meshMaterial.isNull() && m_meshMaterial->getDxLibShader3DParam().useOriginalShader()) DxLib::MV1SetUseOrigShader(FALSE);

		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	int MeshDrawer::getMeshID() const
	{
		return m_meshID;
	}

	void MeshDrawer::setMeshID(int meshID)
	{
		m_meshID = meshID;
	}

	unsigned int MeshDrawer::getBoneCount() const
	{
		return m_localBoneMatrices.size();
	}

	const Matrix4 & MeshDrawer::getLocalBoneMatrix(int boneIndex)
	{
		return m_localBoneMatrices.at(boneIndex);
	}

	void MeshDrawer::setLocalBoneMatrix(int boneIndex, const Matrix4 & localBoneMatrix)
	{
		m_localBoneMatrices.at(boneIndex) = localBoneMatrix;
	}

	const std::vector<Matrix4>& MeshDrawer::getLocalBoneMatrices() const
	{
		return m_localBoneMatrices;
	}

	void MeshDrawer::setLocalBoneMatrices(const std::vector<Matrix4>& localBoneMatrices)
	{
		m_localBoneMatrices = localBoneMatrices;
	}

	void MeshDrawer::setTextureGraphHandle(int materialIndex, int textureId, bool haveAlpha)
	{
		int drawMeshHandle = Assets3DManager::getMeshAssets()->getMeshHandle(m_meshID).meshHandle;
		int materialDifMapTextureIndex = DxLib::MV1GetMaterialDifMapTexture(drawMeshHandle, materialIndex);

		DxLib::MV1SetTextureGraphHandle(
			drawMeshHandle,
			materialDifMapTextureIndex,
			Assets3DManager::getMeshTextureAssets()->getMeshTextureHandles(textureId),
			(haveAlpha) ? TRUE : FALSE
		);
	}

	const DxLibDraw3DParam & MeshDrawer::getDxLibDraw3DParam() const
	{
		return m_dxLibDraw3DParam;
	}

	void MeshDrawer::setMeshLocalMat(const Matrix4 & localMat)
	{
		m_dxLibDraw3DParam.localMat = localMat;
	}
	void MeshDrawer::setBlendMode(BlendMode blendMode)
	{
		m_dxLibDraw3DParam.blendMode = blendMode;
	}
	void MeshDrawer::setBlendParam(float blendParam)
	{
		m_dxLibDraw3DParam.blendParam = blendParam;
	}
	void MeshDrawer::setUseLight(bool useLight)
	{
		m_dxLibDraw3DParam.useLight = useLight;
	}
	void MeshDrawer::setWriteZBuffer(bool writeZBuffer)
	{
		m_dxLibDraw3DParam.writeZBuffer = writeZBuffer;
	}
	void MeshDrawer::useRenderTarget(int renderTargetId)
	{
		m_dxLibDraw3DParam.renderTargetId = renderTargetId;
	}
	void MeshDrawer::unUseRenderTarget()
	{
		m_dxLibDraw3DParam.renderTargetId = -1;
	}

	void setConstantBuffer(int slot, ShaderType targetShaderType, int shaderConstantBufferHandle)
	{
		DxLib::SetShaderConstantBuffer(shaderConstantBufferHandle, targetShaderType, slot);
	}

	void setShaderTexture(int stageIndex, int texAddress, int graphHandle)
	{
		DxLib::SetTextureAddressMode(texAddress, stageIndex);
		DxLib::SetUseTextureToShader(stageIndex, graphHandle);
	}
}
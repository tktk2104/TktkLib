#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawer.h"

#include <string>
#include <algorithm>
#include <d3d11.h>
#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"
#include "TktkDirectX11Wrapper/Graphics/Skeleton/Skeleton.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/Camera/Camera.h"
#include "TktkDirectX11Wrapper/Graphics/Light/Light.h"

namespace tktk
{
	MeshDrawer::MeshDrawer(
		float drawPriority,
		int cameraId,
		int meshId,
		int skeltonId,
		const std::vector<int> & materialIdArray
	)
		: ComponentBase(drawPriority)
		, m_cameraId(cameraId)
		, m_meshId(meshId)
		, m_skeltonId(skeltonId)
		, m_materialIdArray(materialIdArray)
	{
		std::fill(
			std::begin(m_localBoneMatrices),
			std::end(m_localBoneMatrices),
			Matrix4::identity
		);
	}

	MeshDrawer::~MeshDrawer()
	{
	}

	void MeshDrawer::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.isNull())
		{
			throw std::runtime_error("MeshDrawer Transform3D not found");
		}
	}

	void MeshDrawer::draw() const
	{
		MeshData* meshDataPtr = Mesh::getDataPtr(m_meshId);

		setVertexBuffer(meshDataPtr->getVertexBuffer());
		setIndexBuffer(meshDataPtr->getIndexBuffer());

		Matrix4 worldMat = m_transform3D->calculateWorldMatrix();

		std::array<Matrix4, 256U> skinnedBoneMat;
		calculateSkinnedBoneMatrices(&skinnedBoneMat, m_skeltonId, worldMat);

		std::for_each(
			std::begin(m_materialIdArray),
			std::end(m_materialIdArray),
			[this, &worldMat, &skinnedBoneMat](int materialId) { drawUseMaterial(materialId, worldMat, skinnedBoneMat); }
		);
	}

	int MeshDrawer::getSkeltonId() const
	{
		return m_skeltonId;
	}

	void MeshDrawer::setLocalBoneMatrices(std::array<Matrix4, 256U> boneMatrices, unsigned int boneCount)
	{
		std::copy_n(
			std::begin(boneMatrices),
			boneCount,
			std::begin(m_localBoneMatrices)
		);
	}

	void MeshDrawer::setVertexBuffer(const VertexBuffer& vertexBuffer) const
	{
		ID3D11Buffer* rawVertexBuffer = vertexBuffer.getVertexBufferPtr();
		unsigned int stride = vertexBuffer.getStride();
		unsigned int offset = vertexBuffer.getOffset();

		Screen::getDeviceContextPtr()->IASetVertexBuffers(
			0,
			1,
			&rawVertexBuffer,
			&stride,
			&offset
		);
	}

	void MeshDrawer::setIndexBuffer(const IndexBuffer& indexBuffer) const
	{
		Screen::getDeviceContextPtr()->IASetIndexBuffer(
			indexBuffer.getBufferPtr(),
			DXGI_FORMAT_R32_UINT,
			0
		);
	}

	void MeshDrawer::calculateSkinnedBoneMatrices(std::array<Matrix4, 256U>* result, int skeltonId, const Matrix4 & worldMat) const
	{
		if (skeltonId == -10)
		{
			(*result)[0] = Matrix4::identity;
			return;
		}

		const SkeletonData& skeletonData = Skeleton::getData(skeltonId);
		const auto boneArray = skeletonData.getBoneArray();

		result->at(0) = m_localBoneMatrices.at(0) * boneArray.at(0).transform * worldMat;
		for (unsigned int i = 1U; i < boneArray.size(); ++i)
		{
			result->at(i) = m_localBoneMatrices.at(i) * boneArray.at(i).transform * result->at(boneArray.at(i).parentId);
		}

		std::for_each(
			std::begin(boneArray),
			std::end(boneArray),
			[result](auto& node) { result->at(node.id) = node.inverse * result->at(node.id); }
		);
	}

	void MeshDrawer::drawUseMaterial(int materialId, const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const
	{
		MaterialData* materialDataPtr = Material::getDataPtr(materialId);

		std::for_each(
			std::begin(materialDataPtr->getUseTextureIdMap()),
			std::end(materialDataPtr->getUseTextureIdMap()),
			[this](const auto& node) { applyTexture(node.first, node.second); }
		);

		// 頂点シェーダーで使用する定数バッファに情報を詰め詰め
		const VertexShaderData& vsData = VertexShader::getData(materialDataPtr->getUseVertexShaderId());
		updateConstantBuffer(
			vsData.getUseConstantBufferId(),
			worldMat,
			skinnedBoneMat,
			materialDataPtr,
			materialDataPtr->getSetVSConstantBufferParamMap()
		);
		vsData.beginVertexShader();

		const PixelShaderData& psData = PixelShader::getData(materialDataPtr->getUsePixelShaderId());
		// 頂点シェーダーとピクセルシェーダーで使用する定数バッファが違ったら
		if (materialDataPtr->getUseVertexShaderId() != materialDataPtr->getUsePixelShaderId())
		{
			// ピクセルシェーダーで使用する定数バッファに情報を詰め詰め
			updateConstantBuffer(
				psData.getUseConstantBufferId(),
				worldMat,
				skinnedBoneMat,
				materialDataPtr,
				materialDataPtr->getSetPSConstantBufferParamMap()
			);
		}
		psData.beginShader();

		// ドローコール
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Screen::getDeviceContextPtr()->DrawIndexed(materialDataPtr->getIndexBufferUseCount(), materialDataPtr->getIndexBufferStartPos(), 0U);
	}

	void MeshDrawer::applyTexture(unsigned int slot, int textureId) const
	{
		const Texture2DData& texture2D = Texture2D::getData(textureId);

		ID3D11ShaderResourceView* shaderResourceView = texture2D.getShaderResourceViewPtr();
		ID3D11SamplerState* samplerState = texture2D.getSamplerStatePtr();

		Screen::getDeviceContextPtr()->PSSetShaderResources(slot, 1, &shaderResourceView);
		Screen::getDeviceContextPtr()->PSSetSamplers(slot, 1, &samplerState);
	}

	void MeshDrawer::updateConstantBuffer(int constantBufferId, const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat, MaterialData* materialDataPtr, const std::unordered_map<int, SafetyVoidPtr>& setConstantBufferParamMap) const
	{
		ConstantBufferData * bufferData = ConstantBuffer::getDataPtr(constantBufferId);
		CameraData* cameraData = Camera::getDataPtr(m_cameraId);

		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_worldMatrix,			worldMat);
		bufferData->setBufferParamArray(SYSTEM_CONSTANT_BUFFER_PARAM_boneMatrices,		skinnedBoneMat.data(), skinnedBoneMat.size());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_viewMatrix,				*cameraData->getViewMatrixPtr());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_projectionMatrix,		*cameraData->getProjectionMatrixPtr());

		const auto& enableLightList = Light::createEnableLightList();
		int count = std::count_if(std::begin(enableLightList), std::end(enableLightList), [](const auto&) { return true; });

		if (count != 0)
		{
			LightData* lightDataPtr = *(std::begin(enableLightList));

			bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_lightAmbientColor,	*lightDataPtr->getAmbientColorPtr());
			bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_lightDiffuseColor,	*lightDataPtr->getDiffuseColorPtr());
			bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_lightSpecularColor, *lightDataPtr->getSpecularColorPtr());
			bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_lightPosition,		*lightDataPtr->getPositionPtr());
		}

		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_materialAmbientColor,	*materialDataPtr->getAmbientColorPtr());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_materialDiffuseColor,	*materialDataPtr->getDiffuseColorPtr());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_materialSpecularColor,	*materialDataPtr->getSpecularColorPtr());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_materialEmissionColor,	*materialDataPtr->getEmissionColorPtr());
		bufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_materialShininess,		*materialDataPtr->getShininessPtr());

		std::for_each(
			std::begin(setConstantBufferParamMap),
			std::end(setConstantBufferParamMap),
			[&bufferData](const auto& pair) { bufferData->setBufferParam(pair.first, pair.second); }
		);
		bufferData->updateBuffer();
	}
}
#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawer.h"

#include <string>
#include <algorithm>
#include <d3d11.h>
#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MeshConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MaterialConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/LightConstantBufferData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendState.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilState.h"
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerState.h"
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
		const std::vector<int> & materialIdArray,
		int blendStateId,
		const Color& blendRate,
		int depthStencilStateId,
		int rasterizerStateId
	)
		: ComponentBase(drawPriority)
		, m_cameraId(cameraId)
		, m_meshId(meshId)
		, m_skeltonId(skeltonId)
		, m_materialIdArray(materialIdArray)
		, m_blendStateId(blendStateId)
		, m_blendRate(blendRate)
		, m_depthStencilStateId(depthStencilStateId)
		, m_rasterizerStateId(rasterizerStateId)
	{
		std::fill(std::begin(m_localBoneMatrices), std::end(m_localBoneMatrices), Matrix4::identity);
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
		// 描画するメッシュデータを取得
		MeshData* meshDataPtr = Mesh::getDataPtr(m_meshId);

		// 頂点バッファとインデックスバッファをレンダリングパイプラインに設定する
		meshDataPtr->setVertexAndIndexBuffer();

		// ブレンドステートと深度ステンシルを設定する
		std::array<float, 4> factor = { m_blendRate.r, m_blendRate.g, m_blendRate.b, m_blendRate.a };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);

		// ワールド行列を取得する
		Matrix4 worldMat = m_transform3D->calculateWorldMatrix();

		// スキニング行列を計算する
		std::array<Matrix4, 256U> skinnedBoneMat;
		calculateSkinnedBoneMatrices(&skinnedBoneMat, m_skeltonId, worldMat);

		for (unsigned int i = 0; i < meshDataPtr->getMaterialSlotCount(); i++)
		{
			drawUseMaterial(i, meshDataPtr, worldMat, skinnedBoneMat);
		}
	}

	const std::array<Matrix4, 256U>& MeshDrawer::getLocalBoneMatrices() const
	{
		return m_localBoneMatrices;
	}

	void MeshDrawer::setLocalBoneMatrices(const std::array<Matrix4, 256U>& boneMatrices, unsigned int boneCount)
	{
		std::copy_n(
			std::begin(boneMatrices),
			boneCount,
			std::begin(m_localBoneMatrices)
		);
	}

	int MeshDrawer::getCameraId() const
	{
		return m_cameraId;
	}

	int MeshDrawer::getMeshId() const
	{
		return m_meshId;
	}

	int MeshDrawer::getSkeltonId() const
	{
		return m_skeltonId;
	}

	const std::vector<int>& MeshDrawer::getMaterialIdArray() const
	{
		return m_materialIdArray;
	}

	int MeshDrawer::getBlendStateId() const
	{
		return m_blendStateId;
	}

	const Color & MeshDrawer::getBlendRate() const
	{
		return m_blendRate;
	}

	void MeshDrawer::setBlendRate(const Color & rate)
	{
		m_blendRate = rate;
	}

	void MeshDrawer::setCameraIdImpl(int id)
	{
		m_cameraId = id;
	}

	void MeshDrawer::setMeshIdImpl(int id)
	{
		m_meshId = id;
	}

	void MeshDrawer::setSkeltonIdImpl(int id)
	{
		m_skeltonId = id;
	}

	void MeshDrawer::setMaterialIdArrayImpl(const std::vector<int>& idArray)
	{
		m_materialIdArray = idArray;
	}

	void MeshDrawer::setBlendStateIdImpl(int id)
	{
		m_blendStateId = id;
	}

	void MeshDrawer::setDepthStencilStateIdImpl(int id)
	{
		m_depthStencilStateId = id;
	}

	void MeshDrawer::setRasterizerStateIdImpl(int id)
	{
		m_rasterizerStateId;
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

	void MeshDrawer::drawUseMaterial(unsigned int materialSlot, const MeshData* meshDataPtr, const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const
	{
		int materialId = m_materialIdArray.at(materialSlot);

		// マテリアル情報を取得
		MaterialData* materialDataPtr = Material::getDataPtr(materialId);

		const auto& useTextureIdArray = materialDataPtr->getParametersRef().getUseTextureIdArray();

		// 描画で使用するテクスチャをシェーダーに登録する
		for (unsigned int i = 0; i < useTextureIdArray.size(); i++)
		{
			const Texture2DData& texture2D = Texture2D::getData(useTextureIdArray.at(i));

			ID3D11ShaderResourceView* shaderResourceView = texture2D.getShaderResourceViewPtr();
			ID3D11SamplerState* samplerState = texture2D.getSamplerStatePtr();

			Screen::getDeviceContextPtr()->PSSetShaderResources(i, 1, &shaderResourceView);
			Screen::getDeviceContextPtr()->PSSetSamplers(i, 1, &samplerState);
		}

		for (const auto& node : materialDataPtr->getParametersRef().getConstantBufferSetData())
		{
			auto bufferPtr = ConstantBuffer::getDataPtr(node.first);
			bufferPtr->setBufferData(node.second);
			bufferPtr->updateBuffer();
		}

		// メッシュ情報用の定数バッファを更新する
		updateMeshBuffer(worldMat, skinnedBoneMat);
		// マテリアル情報用の定数バッファを更新する
		updateMaterialBuffer(materialDataPtr);
		// ライト情報用の定数バッファを更新する
		updateLightBuffer();

		// ラスタライザステートをセット
		RasterizerState::getData(m_rasterizerStateId).setState();

		// 描画に使用するシェーダーの設定を行う
		VertexShader::getData(materialDataPtr->getUseVertexShaderId()).beginVertexShader();
		PixelShader::getData(materialDataPtr->getUsePixelShaderId()).beginShader();

		meshDataPtr->setPrimitiveTopology();

		// ドローコール
		Screen::getDeviceContextPtr()->DrawIndexed(meshDataPtr->getSubset(materialSlot).indexBufferUseCount, meshDataPtr->getSubset(materialSlot).indexBufferStartPos, 0U);
	}

	void MeshDrawer::updateMeshBuffer(const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const
	{
		// メッシュ情報用の定数バッファを取得
		ConstantBufferData * meshBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Mesh);

		// 描画に使用するカメラ情報を取得
		CameraData* cameraData = Camera::getDataPtr(m_cameraId);

		// メッシュ情報を定数バッファに登録
		MeshConstantBufferData meshConstantBufferData;
		meshConstantBufferData.worldMatrix = worldMat;
		memcpy(meshConstantBufferData.boneMatrices, skinnedBoneMat.data(), sizeof(Matrix4) * skinnedBoneMat.size());
		meshConstantBufferData.viewMatrix = *cameraData->getViewMatrixPtr();
		meshConstantBufferData.projectionMatrix = *cameraData->getProjectionMatrixPtr();
		meshBufferData->setBufferData(std::move(meshConstantBufferData));

		meshBufferData->updateBuffer();
	}

	void MeshDrawer::updateMaterialBuffer(MaterialData* materialDataPtr) const
	{
		// マテリアル情報用の定数バッファを取得
		ConstantBufferData * materialBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Material);
		MaterialConstantBufferData materialConstantBufferData;
		materialConstantBufferData.materialAmbientColor = materialDataPtr->getParametersRef().getAmbientColor();
		materialConstantBufferData.materialDiffuseColor = materialDataPtr->getParametersRef().getDiffuseColor();
		materialConstantBufferData.materialSpecularColor = materialDataPtr->getParametersRef().getSpecularColor();
		materialConstantBufferData.materialEmissionColor = materialDataPtr->getParametersRef().getEmissionColor();
		materialConstantBufferData.materialShininess = materialDataPtr->getParametersRef().getShininess();
		materialBufferData->setBufferData(std::move(materialConstantBufferData));

		materialBufferData->updateBuffer();
	}

	void MeshDrawer::updateLightBuffer() const
	{
		// ライト情報用の定数バッファを取得
		ConstantBufferData * lightBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Light);

		// 有効なライトのリストを取得
		const auto& enableLightList = Light::createEnableLightList();
		int count = std::count_if(std::begin(enableLightList), std::end(enableLightList), [](const auto&) { return true; });

		if (count != 0)
		{
			// ライト情報を定数バッファに登録
			LightData* lightDataPtr = *(std::begin(enableLightList));
			LightConstantBufferData lightConstantBufferData;
			lightConstantBufferData.lightAmbientColor = lightDataPtr->getAmbientColor();
			lightConstantBufferData.lightDiffuseColor = lightDataPtr->getDiffuseColor();
			lightConstantBufferData.lightSpecularColor = lightDataPtr->getSpecularColor();
			lightConstantBufferData.lightPosition = lightDataPtr->getPosition();
			lightBufferData->setBufferData(std::move(lightConstantBufferData));

			lightBufferData->updateBuffer();
		}
	}
}
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
		int depthStencilStateId
	)
		: ComponentBase(drawPriority)
		, m_cameraId(cameraId)
		, m_meshId(meshId)
		, m_skeltonId(skeltonId)
		, m_materialIdArray(materialIdArray)
		, m_blendStateId(blendStateId)
		, m_blendRate(blendRate)
		, m_depthStencilStateId(depthStencilStateId)
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
		// �`�悷�郁�b�V���f�[�^���擾
		MeshData* meshDataPtr = Mesh::getDataPtr(m_meshId);

		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ肷��
		meshDataPtr->setVertexAndIndexBuffer();

		// �u�����h�X�e�[�g�Ɛ[�x�X�e���V����ݒ肷��
		std::array<float, 4> factor = { m_blendRate.r, m_blendRate.g, m_blendRate.b, m_blendRate.a };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);

		// ���[���h�s����擾����
		Matrix4 worldMat = m_transform3D->calculateWorldMatrix();

		// �X�L�j���O�s����v�Z����
		std::array<Matrix4, 256U> skinnedBoneMat;
		calculateSkinnedBoneMatrices(&skinnedBoneMat, m_skeltonId, worldMat);

		for (unsigned int i = 0; i < meshDataPtr->getMaterialSlotCount(); i++)
		{
			drawUseMaterial(i, meshDataPtr->getSubset(i), worldMat, skinnedBoneMat);
		}
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

	void MeshDrawer::drawUseMaterial(unsigned int materialSlot, const Subset& subset, const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const
	{
		int materialId = m_materialIdArray.at(materialSlot);

		// �}�e���A�������擾
		MaterialData* materialDataPtr = Material::getDataPtr(materialId);

		const auto& useTextureIdArray = materialDataPtr->getParametersRef().getUseTextureIdArray();

		// �`��Ŏg�p����e�N�X�`�����V�F�[�_�[�ɓo�^����
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

		// ���b�V�����p�̒萔�o�b�t�@���X�V����
		updateMeshBuffer(worldMat, skinnedBoneMat);
		// �}�e���A�����p�̒萔�o�b�t�@���X�V����
		updateMaterialBuffer(materialDataPtr);
		// ���C�g���p�̒萔�o�b�t�@���X�V����
		updateLightBuffer();

		// �`��Ɏg�p����V�F�[�_�[�̐ݒ���s��
		VertexShader::getData(materialDataPtr->getUseVertexShaderId()).beginVertexShader();
		PixelShader::getData(materialDataPtr->getUsePixelShaderId()).beginShader();

		// �h���[�R�[��
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Screen::getDeviceContextPtr()->DrawIndexed(subset.indexBufferUseCount, subset.indexBufferStartPos, 0U);
	}

	void MeshDrawer::updateMeshBuffer(const Matrix4 & worldMat, const std::array<Matrix4, 256U>& skinnedBoneMat) const
	{
		// ���b�V�����p�̒萔�o�b�t�@���擾
		ConstantBufferData * meshBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Mesh);

		// �`��Ɏg�p����J���������擾
		CameraData* cameraData = Camera::getDataPtr(m_cameraId);

		// ���b�V������萔�o�b�t�@�ɓo�^
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
		// �}�e���A�����p�̒萔�o�b�t�@���擾
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
		// ���C�g���p�̒萔�o�b�t�@���擾
		ConstantBufferData * lightBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Light);

		// �L���ȃ��C�g�̃��X�g���擾
		const auto& enableLightList = Light::createEnableLightList();
		int count = std::count_if(std::begin(enableLightList), std::end(enableLightList), [](const auto&) { return true; });

		if (count != 0)
		{
			// ���C�g����萔�o�b�t�@�ɓo�^
			LightData* lightDataPtr = *(std::begin(enableLightList));
			LightConstantBufferData lightConstantBufferData;
			lightConstantBufferData.lightAmbientColor = *lightDataPtr->getAmbientColorPtr();
			lightConstantBufferData.lightDiffuseColor = *lightDataPtr->getDiffuseColorPtr();
			lightConstantBufferData.lightSpecularColor = *lightDataPtr->getSpecularColorPtr();
			lightConstantBufferData.lightPosition = *lightDataPtr->getPositionPtr();
			lightBufferData->setBufferData(std::move(lightConstantBufferData));

			lightBufferData->updateBuffer();
		}
	}
}
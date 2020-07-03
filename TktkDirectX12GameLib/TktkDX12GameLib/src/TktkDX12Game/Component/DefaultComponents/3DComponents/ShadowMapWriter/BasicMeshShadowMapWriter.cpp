#include "TktkDX12Game/Component/DefaultComponents/3DComponents/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshId, unsigned int skeletonId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// 深度マップ書き出しに必要な値
		MeshTransformCbuffer transformBufferData{};
		{
			// Transform3Dからワールド行列を取得
			transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();
		}
		
		// カメラ情報
		{
			transformBufferData.viewMatrix = tktkMath::Matrix4::createLookAtLH(
				tktkMath::Vector3(60.0f, 10.0f, -60.0f),
				tktkMath::Vector3(0.0f, 0.0f, 0.0f),
				tktkMath::vec3Up
			);
			transformBufferData.projectionMatrix = tktkMath::Matrix4::createOrthographicLH(40, 40, 1.0f, 100.0f);
		}

		DX12GameManager::writeBasicMeshShadowMap(m_meshId, transformBufferData);
	}
}
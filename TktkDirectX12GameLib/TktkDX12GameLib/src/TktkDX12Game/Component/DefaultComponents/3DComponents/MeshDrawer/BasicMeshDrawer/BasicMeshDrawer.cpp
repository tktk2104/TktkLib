#include "TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void BasicMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		m_animator = getComponent<MeshAnimator>();
	}

	void BasicMeshDrawer::draw() const
	{
		if (!m_animator.expired())
		{
			m_animator->transformSkeleton(m_skeletonId);
		}

		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3Dからワールド行列を取得
			baseArgs.transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

			// 使用するビューポート番号
			baseArgs.viewportId = DX12GameManager::getSystemId(SystemViewportType::Basic);

			// 使用するシザー矩形番号
			baseArgs.scissorRectId = DX12GameManager::getSystemId(SystemScissorRectType::Basic);

			// 使用するレンダーターゲットディスクリプタヒープ番号
			baseArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

			// 使用する深度ステンシルディスクリプタヒープ番号
			baseArgs.dsvDescriptorHeapId = DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::Basic);
		}
		
		// カメラ情報
		{
			baseArgs.transformBufferData.viewMatrix = tktkMath::Matrix4::createLookAtLH(
				tktkMath::Vector3(0.0f, 15.0f, -20.0f),
				tktkMath::Vector3(0.0f, 8.0f, 0.0f),
				tktkMath::vec3Up
			);
			
			baseArgs.transformBufferData.projectionMatrix = tktkMath::Matrix4::createPerspectiveFieldOfViewLH(
				90.0f,
				tktk::DX12GameManager::getWindowSize().x / tktk::DX12GameManager::getWindowSize().y,
				1.0f,
				100.0f
			);
		}

		// ライト情報
		{
			baseArgs.lightBufferData.lightPosition = tktkMath::Vector3(60.0f, 10.0f, -60.0f);

			baseArgs.lightBufferData.lightMatrix
				= tktkMath::Matrix4::createLookAtLH(
					baseArgs.lightBufferData.lightPosition,
					tktkMath::Vector3(0.0f, 0.0f, 0.0f),
					tktkMath::vec3Up
				)
				* tktkMath::Matrix4::createOrthographicLH(40, 40, 1.0f, 100.0f);
		}

		// メッシュを描画する
		DX12GameManager::drawBasicMesh(m_meshId, baseArgs);
	}
}
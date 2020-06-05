#include "TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void BasicMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform3D");
		}
	}

	void BasicMeshDrawer::draw() const
	{
		static float angle = 0.0f;

		angle += 1.0f;

		MeshDrawFuncBaseArgs baseArgs{};
		baseArgs.worldMatrix = m_transform->calculateWorldMatrix() * tktkMath::Matrix4::createRotationY(angle);

		// ÉJÉÅÉâèÓïÒ
		{
			baseArgs.viewMatrix = tktkMath::Matrix4::createLookAtLH(
				tktkMath::Vector3(0.0f, 8.0f, -15.0f),
				tktkMath::Vector3(0.0f, 8.0f, 0.0f),
				tktkMath::vec3Up
			);

			baseArgs.projectionMatrix = tktkMath::Matrix4::createPerspectiveFieldOfViewLH(
				90.0f,
				tktk::DX12GameManager::getWindowSize().x / tktk::DX12GameManager::getWindowSize().y,
				1.0f,
				100.0f
			);
		}

		baseArgs.lightPosition = { 0.0f, 10.0f, -100.0f };
		/*for (auto& node : baseArgs.boneMatrix)
		{
			node = tktkMath::mat4Identity;
		}*/
		baseArgs.viewportId				= DX12GameManager::getSystemId(SystemViewportType::Basic);
		baseArgs.scissorRectId			= DX12GameManager::getSystemId(SystemScissorRectType::Basic);
		baseArgs.rtvDescriptorHeapId	= m_useRtvDescriptorHeapId;
		baseArgs.dsvDescriptorHeapId	= DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::Basic);

		DX12GameManager::drawBasicMesh(m_meshId, baseArgs);
	}
}
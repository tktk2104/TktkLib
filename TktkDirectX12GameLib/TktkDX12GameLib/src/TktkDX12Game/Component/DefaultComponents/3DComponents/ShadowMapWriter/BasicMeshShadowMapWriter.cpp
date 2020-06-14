#include "TktkDX12Game/Component/DefaultComponents/3DComponents/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
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
		MeshWriteShadowFuncBaseArgs baseArgs{};
		baseArgs.worldMatrix = m_transform->calculateWorldMatrix();

		// ƒJƒƒ‰î•ñ
		{
			baseArgs.viewMatrix = tktkMath::Matrix4::createLookAtLH(
				tktkMath::Vector3(60.0f, 10.0f, -60.0f),
				tktkMath::Vector3(0.0f, 8.0f, 0.0f),
				tktkMath::vec3Up
			);
			baseArgs.projectionMatrix = tktkMath::Matrix4::createOrthographicLH(40, 40, 1.0f, 100.0f);
		}
		// œî•ñ
		for (auto& node : baseArgs.boneMatrix)
		{
			node = tktkMath::mat4Identity;
		}
		DX12GameManager::writeBasicMeshShadowMap(m_meshId, baseArgs);
	}
}
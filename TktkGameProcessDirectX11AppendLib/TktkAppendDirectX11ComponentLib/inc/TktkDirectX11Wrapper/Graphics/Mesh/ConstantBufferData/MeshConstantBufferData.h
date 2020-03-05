#ifndef MESH_CONSTANT_BUFFER_DATA_H_
#define MESH_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>

namespace tktk
{
	// ���b�V���`��̒萔�o�b�t�@�̌`��
	struct MeshConstantBufferData
	{
		Matrix4 worldMatrix;
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;
		Matrix4 boneMatrices[256];
	};
}
#endif // !MESH_CONSTANT_BUFFER_DATA_H_
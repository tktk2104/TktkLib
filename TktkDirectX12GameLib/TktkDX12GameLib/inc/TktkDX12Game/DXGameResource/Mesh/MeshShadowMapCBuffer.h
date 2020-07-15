#ifndef MESH_SHADOW_MAP_CBUFFER_H_
#define MESH_SHADOW_MAP_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �V���h�E�}�b�v���g�����`��ɕK�v�ȏ��
	struct MeshShadowMapCBuffer
	{
		// �V���h�E�}�b�v�`��Ɏg�p�����r���[�v���W�F�N�V�����s��
		tktkMath::Matrix4	shadowMapViewProjMat	{ tktkMath::mat4Identity };
	};
}
#endif // !MESH_SHADOW_MAP_CBUFFER_H_
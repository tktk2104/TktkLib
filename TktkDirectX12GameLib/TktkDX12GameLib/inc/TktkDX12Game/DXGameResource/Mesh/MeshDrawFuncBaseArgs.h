#ifndef MESH_DRAW_FUNC_BASE_ARGS_H_
#define MESH_DRAW_FUNC_BASE_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshTransformCbuffer.h"
#include "MeshShadowMapCBuffer.h"
#include "BasicMesh/BasicMeshLightCbuffer.h"

namespace tktk
{
	// ���b�V���`��ɕK�v�Ȉ���
	struct MeshDrawFuncBaseArgs
	{
		// �g�p����r���[�|�[�g��ID
		unsigned int			viewportId;

		// �g�p����V�U�[��`��ID
		unsigned int			scissorRectId;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�vID
		unsigned int			rtvDescriptorHeapId;

		// �g�p����[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�vID
		unsigned int			dsvDescriptorHeapId;

		// ���b�V���̍��W�ϊ����
		MeshTransformCbuffer	transformBufferData{};

		// �V���h�E�}�b�v���g�����`��ɕK�v�ȏ��
		MeshShadowMapCBuffer	shadowMapBufferData{};

		// �ʏ탁�b�V���̃��C�e�B���O���
		BasicMeshLightCbuffer	lightBufferData{};
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_
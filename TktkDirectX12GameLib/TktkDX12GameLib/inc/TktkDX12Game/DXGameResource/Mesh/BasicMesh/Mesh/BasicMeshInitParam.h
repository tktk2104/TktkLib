#ifndef BASIC_MESH_INIT_PARAM_H_
#define BASIC_MESH_INIT_PARAM_H_

#include <vector>
#include "../Subset.h"

namespace tktk
{
	// �ʏ탁�b�V�������Ƃ��ɕK�v�ȏ��
	struct BasicMeshInitParam
	{
		// �g�����_�o�b�t�@��ID
		unsigned int useVertexBufferId;

		// �g���C���f�b�N�X�o�b�t�@��ID
		unsigned int useIndexBufferId;

		// ���b�V�������C���f�b�N�X�̑���
		unsigned int indexNum;

		// �T�u�Z�b�g�i�g�p����}�e���A�����j
		std::vector<Subset> materialSlots;
	};
}
#endif // !BASIC_MESH_INIT_PARAM_H_
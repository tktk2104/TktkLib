#ifndef BASIC_MESH_PMD_LOADER_H_
#define BASIC_MESH_PMD_LOADER_H_

#include "BasicMeshLoadPmdArgs.h"
#include "BasicMeshLoadPmdReturnValue.h"

namespace tktk
{
	// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class BasicMeshPmdLoader
	{
	public:

		// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);
	};
}
#endif // !BASIC_MESH_PMD_LOADER_H_

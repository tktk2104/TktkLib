#ifndef BASIC_MESH_DATA_H_
#define BASIC_MESH_DATA_H_

#include <vector>
#include "BasicMeshInitParam.h"
#include "../Subset.h"
#include "../../MeshDrawFuncBaseArgs.h"

namespace tktk
{
	// �ʏ탁�b�V�������Ǘ�����N���X
	class BasicMeshData
	{
	public:

		BasicMeshData(const BasicMeshInitParam& initParam);

	public:

		// �V���h�E�}�b�v����������
		void writeShadowMap();

		// �ʏ탁�b�V����`�悷��
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs);

	private:

		unsigned int m_useVertexBufferId;
		unsigned int m_useIndexBufferId;

		unsigned int m_indexNum;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_
#ifndef BASIC_MESH_DATA_H_
#define BASIC_MESH_DATA_H_

#include <vector>
#include "BasicMeshInitParam.h"
#include "../Subset.h"
#include "../../MeshWriteShadowFuncBaseArgs.h"
#include "../../MeshDrawFuncBaseArgs.h"

namespace tktk
{
	class BasicMeshData
	{
	public:

		BasicMeshData(const BasicMeshInitParam& initParam);

	public:

		void writeShadowMap(const MeshWriteShadowFuncBaseArgs& baseArgs);

		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs);

	private:

		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̒萔�o�b�t�@���X�V����
		void updateShadowMapCbuffer(const MeshWriteShadowFuncBaseArgs& baseArgs);

	private:

		unsigned int m_useVertexBufferId;
		unsigned int m_useIndexBufferId;

		unsigned int m_indexNum;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_
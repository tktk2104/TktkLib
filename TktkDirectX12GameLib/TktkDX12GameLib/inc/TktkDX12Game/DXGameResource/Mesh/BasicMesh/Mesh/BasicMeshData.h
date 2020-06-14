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

		// 通常メッシュ版シャドウマップ描画用の定数バッファを更新する
		void updateShadowMapCbuffer(const MeshWriteShadowFuncBaseArgs& baseArgs);

	private:

		unsigned int m_useVertexBufferId;
		unsigned int m_useIndexBufferId;

		unsigned int m_indexNum;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_
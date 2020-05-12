#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_


#include "BasicMeshData.h"
#include "../../../HeapArray/HeapArray.h"

namespace tktk
{
	class BasicMesh
	{
	public:

		BasicMesh(unsigned int basicMeshNum);
	
	public:

		void craete(unsigned int id, const BasicMeshInitParam& initParam);

		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

	private:

		HeapArray<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_
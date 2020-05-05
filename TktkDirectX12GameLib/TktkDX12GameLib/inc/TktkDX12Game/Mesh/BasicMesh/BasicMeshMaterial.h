#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include "BasicMeshMaterialData.h"
#include "../../HeapArray/HeapArray.h"

namespace tktk
{
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		void create(unsigned int id, const BasicMeshMaterialInitParam& initparam);

		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_
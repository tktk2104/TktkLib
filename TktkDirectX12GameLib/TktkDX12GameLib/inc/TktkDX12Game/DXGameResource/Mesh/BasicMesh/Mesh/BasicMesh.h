#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include "BasicMeshData.h"
#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>

namespace tktk
{
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, unsigned int basicMeshNum);
	
	public:

		void craete(unsigned int id, const BasicMeshInitParam& initParam);

		void writeShadowMap(unsigned int id, const MeshWriteShadowFuncBaseArgs& baseArgs);

		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

	private:

		void createWriteShadowMapRootSignature();

		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath);

	private:

		HeapArray<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_
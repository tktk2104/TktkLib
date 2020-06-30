#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicMeshData.h"

namespace tktk
{
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, unsigned int basicMeshNum);
	
	public:

		void craete(unsigned int id, const BasicMeshInitParam& initParam);

		void writeShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

	private:

		void createWriteShadowMapRootSignature();

		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath);

		void updateMeshTransformCbuffer(const MeshTransformCbuffer& transformBufferData);

		void updateBasicMeshLightCbuffer(const BasicMeshLightCbuffer& lightBufferData);

	private:

		HeapArray<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_
#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateInitParam.h>
#undef min
#undef max
#include "BasicMeshMaterial.h"

namespace tktk
{
	class BasicMesh
	{
	public:

		BasicMesh(const tktk::ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum);
	
	public:

		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initparam);

		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);
	
	private:

		void createRootSignature();

		void createGraphicsPipeLineState(const tktk::ShaderFilePaths& shaderFilePaths);

	private:

		BasicMeshMaterial m_basicMeshMaterial;
	};
}
#endif // !BASIC_MESH_H_
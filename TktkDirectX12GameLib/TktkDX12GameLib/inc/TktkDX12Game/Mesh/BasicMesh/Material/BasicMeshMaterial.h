#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateInitParam.h>
#undef min
#undef max
#include "BasicMeshMaterialData.h"
#include "../../../HeapArray/HeapArray.h"

namespace tktk
{
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const tktk::ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		void create(unsigned int id, const BasicMeshMaterialInitParam& initparam);

		void drawUseMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs);

	private:

		void createRootSignature();

		void createGraphicsPipeLineState(const tktk::ShaderFilePaths& shaderFilePaths);

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_
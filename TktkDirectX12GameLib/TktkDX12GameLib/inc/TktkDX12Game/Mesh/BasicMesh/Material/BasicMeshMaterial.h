#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#undef min
#undef max
#include "BasicMeshMaterialData.h"
#include <TktkContainer/HeapArray/HeapArray.h>

namespace tktk
{
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		void create(unsigned int id, const BasicMeshMaterialInitParam& initparam);

		void drawUseMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs);

	private:

		void createRootSignature();

		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths);

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_
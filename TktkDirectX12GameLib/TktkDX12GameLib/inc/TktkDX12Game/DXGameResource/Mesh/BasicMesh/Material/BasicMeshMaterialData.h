#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

#include "BasicMeshMaterialInitParam.h"
#include "../../MeshDrawFuncBaseArgs.h"
#include "../../MeshMaterialDrawFuncArgs.h"

namespace tktk
{
	class BasicMeshMaterialData
	{
	public:

		BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);
		~BasicMeshMaterialData() = default;

	public:

		void drawUseMaterial(const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs);

	private:

		// 通常メッシュ用の定数バッファを更新する
		void updateBasicMeshConstantBuffer(const MeshDrawFuncBaseArgs& baseArgs);

	private:

		unsigned int		m_createDescriptorHeapId;
		tktkMath::Color		m_materialAmbient;
		tktkMath::Color		m_materialDiffuse;
		tktkMath::Color		m_materialSpecular;
		tktkMath::Color		m_materialEmissive;
		float				m_materialShiniess;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_
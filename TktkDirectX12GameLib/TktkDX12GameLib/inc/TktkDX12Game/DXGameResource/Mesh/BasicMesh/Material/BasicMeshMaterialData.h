#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

#include "BasicMeshMaterialInitParam.h"
#include "../../MeshDrawFuncBaseArgs.h"

namespace tktk
{
	class BasicMeshMaterialData
	{
	public:

		BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);
		~BasicMeshMaterialData() = default;

	public:

		void setMaterialData();

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
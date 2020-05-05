#include "TktkDX12Game/Mesh/BasicMesh/BasicMeshMaterial.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	BasicMeshMaterial::BasicMeshMaterial(unsigned int basicMeshMaterialNum)
		: m_basicMeshMaterialArray(basicMeshMaterialNum)
	{
	}

	void BasicMeshMaterial::create(unsigned int id, const BasicMeshMaterialInitParam& initparam)
	{
		m_basicMeshMaterialArray.emplaceAt(id, initparam);
	}

	void BasicMeshMaterial::drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.at(id);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->drawBasicMesh(baseArgs);
	}
}
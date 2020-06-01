#include "TktkDX12Game/Mesh/BasicMesh/Mesh/BasicMesh.h"

namespace tktk
{
	BasicMesh::BasicMesh(unsigned int basicMeshNum)
		: m_basicMeshArray(basicMeshNum)
	{
	}

	void BasicMesh::craete(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_basicMeshArray.emplaceAt(id, initParam);
	}

	void BasicMesh::drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_basicMeshArray.at(id)->drawMesh(baseArgs);
	}
}
#include "TktkDX12Game/DXGameResource/_SystemDXGameResourceIdGetter/SystemDXGameResourceIdGetter.h"

namespace tktk
{
	SystemDXGameResourceIdGetter::SystemDXGameResourceIdGetter(DXGameResourceNum* resourceNum)
		: m_basicDxGameResourceNum(*resourceNum)
	{
		resourceNum->basicMeshNum			+= SystemBasicMeshNum;
		resourceNum->basicMeshMaterialNum	+= SystemBasicMeshMaterialNum;
		resourceNum->postEffectMaterialNum	+= SystemPostEffectMaterialNum;
	}

	unsigned int SystemDXGameResourceIdGetter::getSystemId(SystemBasicMeshType type) const
	{
		return m_basicDxGameResourceNum.basicMeshNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemDXGameResourceIdGetter::getSystemId(SystemBasicMeshMaterialType type) const
	{
		return m_basicDxGameResourceNum.basicMeshMaterialNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemDXGameResourceIdGetter::getSystemId(SystemPostEffectMaterialType type) const
	{
		return m_basicDxGameResourceNum.postEffectMaterialNum + static_cast<unsigned int>(type);
	}
}

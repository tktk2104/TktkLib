#ifndef DX3D_BASE_OBJECTS_INIT_PARAM_H_
#define DX3D_BASE_OBJECTS_INIT_PARAM_H_

#include "../DX3DResource/DX3DResourceInitParam.h"

namespace tktk
{
	struct DX3DBaseObjectsInitParam
	{
		DX3DResourceInitParam resourceInitParam;

		unsigned int spriteNum;
		unsigned int basicMeshNum;
		unsigned int basicMeshMaterialNum;
		unsigned int postEffectMaterialNum;
	};
}
#endif // !DX3D_BASE_OBJECTS_INIT_PARAM_H_
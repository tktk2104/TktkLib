#ifndef FBX_MATERIAL_DATA_PARAM_H_
#define FBX_MATERIAL_DATA_PARAM_H_

#include <TktkMath/Color.h>

namespace tktk
{
	struct FbxMaterialDataParam
	{
		Color ambient;
		Color diffuse;
		Color specular;
		Color emission;
		float shiniess;
		char textureFileName[128];
		char normalFileName[128];
		void* temp1{ nullptr };
		void* temp2{ nullptr };
	};
}
#endif // !FBX_MATERIAL_DATA_PARAM_H_
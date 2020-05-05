#ifndef BASIC_MESH_MATERIAL_INIT_PARAM_H_
#define BASIC_MESH_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct BasicMeshMaterialInitParam
	{
		unsigned int						createDescriptorHeapId;
		unsigned int						useAlbedoMapTextureId;
		unsigned int						useNormalMapTextureId;

		tktkMath::Color						materialAmbient		{ tktkMath::colorBlack };
		tktkMath::Color						materialDiffuse		{ tktkMath::colorWhite };
		tktkMath::Color						materialSpecular	{ tktkMath::colorWhite };
		tktkMath::Color						materialEmissive	{ tktkMath::colorWhite };
		float								materialShiniess	{ 1.0f };
	};
}
#endif // !BASIC_MESH_MATERIAL_INIT_PARAM_H_
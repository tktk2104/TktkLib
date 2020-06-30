#ifndef BASIC_MESH_MATERIAL_CBUFFER_H_
#define BASIC_MESH_MATERIAL_CBUFFER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct BasicMeshMaterialCbuffer
	{
		tktkMath::Color	materialAmbient{ tktkMath::colorBlack };
		tktkMath::Color	materialDiffuse{ tktkMath::colorWhite };
		tktkMath::Color	materialSpecular{ tktkMath::colorWhite };
		tktkMath::Color	materialEmissive{ tktkMath::colorWhite };
		float			materialShiniess{ 1.0f };
		float			materialDataPad[3]{ 0.0f, 0.0f, 0.0f };

	};
}
#endif // !BASIC_MESH_MATERIAL_CBUFFER_H_

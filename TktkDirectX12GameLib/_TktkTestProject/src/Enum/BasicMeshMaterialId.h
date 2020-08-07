#ifndef BASIC_MESH_MATERIAL_ID_H_
#define BASIC_MESH_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class BasicMeshMaterialId
{
	MikuMatStart		= 0U,
	MikuMatEnd			= MikuMatStart			+ 15U,
	ElementSphereStart,
	ElementSphereEnd	= ElementSphereStart	+ 10U,

	Count
};

constexpr unsigned int BasicMeshMaterialNum = static_cast<unsigned int>(BasicMeshMaterialId::Count);

#endif // !BASIC_MESH_MATERIAL_ID_H_

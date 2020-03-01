#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/SystemConstantBufferParamLocationType.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>

static void LoadPistolPbrIblMaterial()
{
	tktk::Material::duplicate(MATERIAL_PBR_IBL_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolPbrIblMaterial = tktk::Material::getDataPtr(MATERIAL_PBR_IBL_PISTOL);

	pistolPbrIblMaterial->addUseTextureId(2U, TEXTURE_2D_SPRITE_MeSm);
	pistolPbrIblMaterial->addUseTextureId(3U, TEXTURE_2D_SPRITE_AmOc);
	pistolPbrIblMaterial->addUseTextureId(4U, TEXTURE_2D_SPRITE_CUBE);
	pistolPbrIblMaterial->addUseTextureId(5U, TEXTURE_2D_SPRITE_ENV);

	pistolPbrIblMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::PbrIblMesh);
	pistolPbrIblMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::PbrIblMesh);
}
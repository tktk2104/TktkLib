#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/Texture2D/Asset/MaterialLoadTextureIdManager.h>
#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>

static void LoadPistolPbrIblMaterial()
{
	tktk::Material::duplicate(MATERIAL_PBR_IBL_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolPbrIblMaterial = tktk::Material::getDataPtr(MATERIAL_PBR_IBL_PISTOL);

	pistolPbrIblMaterial->getParametersRef().setUseTextureId(
		tktk::MaterialLoadTextureIdManager::getMaterialTextureId(MATERIAL_PISTOL, 0),
		tktk::MaterialLoadTextureIdManager::getMaterialTextureId(MATERIAL_PISTOL, 1)
	);

	pistolPbrIblMaterial->getParametersRef().addUseTextureId(1000000);//TEXTURE_2D_SPRITE_MeSm
	pistolPbrIblMaterial->getParametersRef().addUseTextureId(TEXTURE_2D_SPRITE_AmOc);
	pistolPbrIblMaterial->getParametersRef().addUseTextureId(TEXTURE_2D_SPRITE_CUBE);
	pistolPbrIblMaterial->getParametersRef().addUseTextureId(TEXTURE_2D_SPRITE_ENV);

	pistolPbrIblMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::PbrIblMesh);
	pistolPbrIblMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::PbrIblMesh);
}
#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/SystemConstantBufferParamLocationType.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>

static void LoadPistolIblMaterial()
{
	tktk::Material::duplicate(MATERIAL_IBL_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolIblMaterial = tktk::Material::getDataPtr(MATERIAL_IBL_PISTOL);

	pistolIblMaterial->clearUseTextureId();
	pistolIblMaterial->addUseTextureId(0U, -(MATERIAL_PISTOL * 100 + 2));
	pistolIblMaterial->addUseTextureId(1U, TEXTURE_2D_SPRITE_CUBE);
	pistolIblMaterial->addUseTextureId(2U, TEXTURE_2D_SPRITE_ENV);

	pistolIblMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::IblMesh);
	pistolIblMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::IblMesh);

	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::albedoColor, Color::white);
	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::metallic, 1.0f);
	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::smoothness, 1.0f);

	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::albedoColor, Color::white);
	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::metallic, 1.0f);
	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::smoothness, 1.0f);
}
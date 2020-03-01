#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/SystemConstantBufferParamLocationType.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>

static void LoadPistolPbrMaterial()
{
	tktk::Material::duplicate(MATERIAL_PBR_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolPbrMaterial = tktk::Material::getDataPtr(MATERIAL_PBR_PISTOL);

	pistolPbrMaterial->clearUseTextureId();
	pistolPbrMaterial->addUseTextureId(0U, -(MATERIAL_PISTOL * 100 + 2));

	pistolPbrMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::PbrMesh);
	pistolPbrMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::PbrMesh);

	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::albedoColor, Color::green);
	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::metallic, 0.5f);
	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::smoothness, 0.5f);

	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::albedoColor, Color::green);
	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::metallic, 0.5f);
	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SystemConstantBufferParamLocationType::smoothness, 0.5f);
}
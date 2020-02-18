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

	pistolPbrMaterial->setUseVertexShaderId(tktk::SYSTEM_VERTEX_SHADER_PBR_MESH);
	pistolPbrMaterial->setUsePixelShaderId(tktk::SYSTEM_PIXEL_SHADER_PBR_MESH);

	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_albedoColor, Color::green);
	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_metallic, 0.5f);
	pistolPbrMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_smoothness, 0.5f);

	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_albedoColor, Color::green);
	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_metallic, 0.5f);
	pistolPbrMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_smoothness, 0.5f);
}
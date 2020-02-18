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

	pistolIblMaterial->setUseVertexShaderId(tktk::SYSTEM_VERTEX_SHADER_IBL_MESH);
	pistolIblMaterial->setUsePixelShaderId(tktk::SYSTEM_PIXEL_SHADER_IBL_MESH);

	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_albedoColor, Color::white);
	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_metallic, 1.0f);
	pistolIblMaterial->settingReservationVSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_smoothness, 1.0f);

	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_albedoColor, Color::white);
	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_metallic, 1.0f);
	pistolIblMaterial->settingReservationPSConstantBufferParam(tktk::SYSTEM_CONSTANT_BUFFER_PARAM_smoothness, 1.0f);
}
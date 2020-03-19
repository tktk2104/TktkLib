#pragma once

#include "CommonIncludePaths.h"

#include <TktkDirectX11Wrapper/Graphics/Texture2D/Asset/MaterialLoadTextureIdManager.h>
#include <TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h>
#include <TktkDirectX11Wrapper/Graphics/Material/Material.h>
#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/SystemConstantBufferId.h>
#include <TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/PbrConstantBufferData.h>

static void LoadPistolIblMaterial()
{
	tktk::Material::duplicate(MATERIAL_IBL_PISTOL, MATERIAL_PISTOL);

	tktk::MaterialData* pistolIblMaterial = tktk::Material::getDataPtr(MATERIAL_IBL_PISTOL);

	pistolIblMaterial->getParametersRef().setUseTextureId(
		tktk::MaterialLoadTextureIdManager::getMaterialTextureId(MATERIAL_PISTOL, 1),
		TEXTURE_2D_SPRITE_CUBE,
		TEXTURE_2D_SPRITE_ENV
	);

	pistolIblMaterial->setUseVertexShaderId(tktk::SystemVertexShaderId::IblMesh);
	pistolIblMaterial->setUsePixelShaderId(tktk::SystemPixelShaderId::IblMesh);

	tktk::PbrConstantBufferData pbrBuffer;
	pbrBuffer.albedoColor = Color::white;
	pbrBuffer.metallic = 1.0f;
	pbrBuffer.smoothness = 1.0f;

	pistolIblMaterial->getParametersRef().setConstantBufferSetData(tktk::SystemConstantBufferId::Pbr, std::move(pbrBuffer));
}